#include "Level.h"

#include "Evolved/Components/Component.h"
#include "Evolved/Messages/Message.h"
#include "Evolved/Messages/MessageTopic.h"
#include "Application/Macros.h"

namespace Evolved {

	CLevel::CLevel() : _initialized(false), _messageTopic(new Messages::CMessageTopic()) {

	}

	CLevel::~CLevel() {
		if(_messageTopic) {
			delete _messageTopic;
			_messageTopic = NULL;
		}

		_entitiesToBeDeleted.clear();
		destroyAllEntities();
	}

	bool CLevel::initialize() {
		assert(!_initialized && "A level can't be initialized twice.");

		// iterate over entities
		FOR_IT_CONST(TEntities, itEntity, _entities) {
			const CEntityData &data = itEntity->second;

			// iterate over entity components and spawn them
			FOR_IT_CONST(TComponents, itComponent, data.components) {
				if(!(*itComponent)->spawn(itEntity->second.data, this)) {
					assert(false && "An entity couldn't be spawned correctly.");
					return false;
				}
			}
		}

		_initialized = true;
		return true;
	}

	bool CLevel::activate() {
		assert(_initialized && "A level can't be activated before being initialized.");

		// iterate over entities (not using a constant iterator because we might have to save data)
		FOR_IT(TEntities, itEntity, _entities) {
			const CEntityData &data = itEntity->second;

			// iterate over entity components and activate them
			FOR_IT_CONST(TComponents, itComponent, data.components) {
				if(!(*itComponent)->activate()) {
					return false;
				}
			}

			// entity was activated correctly, so save that
			itEntity->second.active = true;
		}

		// now that every component is activated, suscribe them all
		suscribeEntities();

		return true;
	}

	void CLevel::deactivate() {
		assert(_initialized && "A level can't be deactivated before being initialized.");

		// unsuscribe components from our message topic
		unsuscribeEntities();

		// iterate over entities
		FOR_IT_CONST(TEntities, itEntity, _entities) {
			const CEntityData &data = itEntity->second;

			// iterate over entity components and deactivate them
			FOR_IT_CONST(TComponents, itComponent, data.components) {
				(*itComponent)->deactivate();
			}
		}
	}

	void CLevel::tick(float secs) {
		assert(_initialized && "A level can't receive tick before being initialized.");

		// iterate over entities
		FOR_IT_CONST(TEntities, itEntity, _entities) {
			const CEntityData &data = itEntity->second;

			// iterate over entity components and pass the tick
			FOR_IT_CONST(TComponents, itComponent, data.components) {
				(*itComponent)->doTick(secs);
			}
		}

		// now that every entity in the level has receive their tick, we can clean up
		// pending entities which were requested to be deleted
		deletePendingEntities();
	}

	bool CLevel::addEntity(const TEntityID &entity, const CEntityData &entityData) {
		TEntities::const_iterator it = _entities.find(entity);

		if(it == _entities.end()) {
			// create a new entry
			_entities[entity] = entityData;

			return true;
		}

		return false;
	}

	bool CLevel::removeEntity(const TEntityID &entity) {
		TEntities::const_iterator it = _entities.find(entity);

		if(it != _entities.end()) {
			_entities.erase(it);
			return true;
		}

		return false;
	}

	TEntityID CLevel::getEntityByName(const std::string &name) const {
		TEntityID entity = CEntityID::UNASSIGNED;

		// iterate over entities
		FOR_IT_CONST(TEntities, itEntity, _entities) {
			if(itEntity->second.name == name) {
				entity = itEntity->first;
				break;
			}
		}

		return entity;
	}

	const std::string &CLevel::getEntityName(const TEntityID &entity) const {
		TEntities::const_iterator it = _entities.find(entity);
		assert(it != _entities.end() && "Given entity doesn't exist in the current level.");

		return it->second.name;
	}

	void CLevel::setEntityName(const TEntityID &entity, const std::string &name) {
		TEntities::iterator it = _entities.find(entity);
		assert(it != _entities.end() && "Given entity doesn't exist in the current level.");

		it->second.name = name;
	}

	const std::string &CLevel::getEntityType(const TEntityID &entity) const {
		TEntities::const_iterator it = _entities.find(entity);
		assert(it != _entities.end() && "Given entity doesn't exist in the current level.");

		return it->second.type;
	}

	void CLevel::setEntityType(const TEntityID &entity, const std::string &type) {
		TEntities::iterator it = _entities.find(entity);
		assert(it != _entities.end() && "Given entity doesn't exist in the current level.");

		it->second.type = type;
	}

	bool CLevel::isEntityActive(const TEntityID &entity) const {
		TEntities::const_iterator it = _entities.find(entity);
		assert(it != _entities.end() && "Given entity doesn't exist in the current level.");

		return it->second.active;
	}

	void CLevel::destroyAllEntities() {
		// iterate over entities
		FOR_IT_CONST(TEntities, itEntity, _entities) {
			const CEntityData &data = itEntity->second;

			// iterate over entity components and delete them
			FOR_IT_CONST(TComponents, itComponent, data.components) {
				delete *itComponent;
			}
		}

		_entities.clear();
	}

	void CLevel::deferDeleteEntity(const TEntityID &entity) {
		_entitiesToBeDeleted.push_back(entity);
	}

	void CLevel::deletePendingEntities() {
		FOR_IT_CONST(TDeferredEntities, it, _entitiesToBeDeleted) {
			// an entity which was requested to be deleted should still be in the
			// level, but there might be an edge case in which something removed
			// an entity from the level and in the same frame its requested for deletion
			TEntities::const_iterator itEntity = _entities.find(*it);
			assert(itEntity != _entities.end() && "An entity marked for deletion doesn't exist in the level.");

			// now delete every component in the entity
			const CEntityData &data = itEntity->second;

			// iterate over entity components and delete them
			FOR_IT_CONST(TComponents, itComponent, data.components) {
				delete *itComponent;
			}
		}

		_entitiesToBeDeleted.clear();
	}

	bool CLevel::sendMessage(const TEntityID &destination, Messages::CMessage *message,
	                         IComponent *emitter) {
		return _messageTopic->sendMessage(destination, message, emitter);
	}

	void CLevel::suscribeEntities() {
		// temporal WishList to pass around components (we're reusing it, instead of creating more)
		Messages::CWishList wishList;

		FOR_IT_CONST(TEntities, itEntity, _entities) {
			const CEntityData &data = itEntity->second;

			FOR_IT_CONST(TComponents, itComponent, data.components) {
				// ask the component to tell which messages are important for it
				(*itComponent)->populateWishList(wishList);

				// now suscribe the component to those messages
				_messageTopic->suscribe(*itComponent, wishList);

				// and clear our temporal WishList, to get ready for next iteration
				wishList.clear();
			}
		}
	}

	void CLevel::unsuscribeEntities() {
		FOR_IT_CONST(TEntities, itEntity, _entities) {
			_messageTopic->unsuscribe(itEntity->first);
		}
	}

}