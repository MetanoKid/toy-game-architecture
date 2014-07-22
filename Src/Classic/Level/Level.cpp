#include "Level.h"

#include "Application/Macros.h"
#include "Classic/Entity/Entity.h"

namespace Classic {

	CLevel::CLevel() : _initialized(false) {

	}

	CLevel::~CLevel() {
		destroyAllEntities();
	}

	bool CLevel::initialize() {
		assert(!_initialized && "A level can't be initialized twice.");

		FOR_IT_CONST(TEntities, it, _entities) {
			CEntity *entity = *it;

			if(!entity->spawn(_entitiesData[entity->getID()], this)) {
				assert(false && "An entity couldn't be spawned correctly.");
				return false;
			}
		}

		_initialized = true;
		return true;
	}

	bool CLevel::activate() {
		assert(_initialized && "A level can't be activated before being initialized.");

		FOR_IT_CONST(TEntities, it, _entities) {
			if(!(*it)->activate()) {
				return false;
			}
		}

		return true;
	}

	void CLevel::deactivate() {
		assert(_initialized && "A level can't be deactivated before being initialized.");

		FOR_IT_CONST(TEntities, it, _entities) {
			(*it)->deactivate();
		}
	}

	void CLevel::tick(float secs) {
		assert(_initialized && "A level can't receive tick before being initialized.");

		FOR_IT_CONST(TEntities, it, _entities) {
			(*it)->tick(secs);
		}
	}

	bool CLevel::addEntity(CEntity *entity, CLevelData data) {
		TEntities::const_iterator it = std::find(_entities.begin(), _entities.end(), entity);

		if(it == _entities.end()) {
			_entities.push_back(entity);

			// also, store the data for this entity for the second step of initialization
			_entitiesData[entity->getID()] = data;
			return true;
		}

		return false;
	}

	bool CLevel::removeEntity(CEntity *entity) {
		TEntities::const_iterator it = std::find(_entities.begin(), _entities.end(), entity);

		if(it != _entities.end()) {
			_entities.erase(it);
			return true;
		}

		return false;
	}

	CEntity *CLevel::getEntityByName(const std::string &name) const {
		FOR_IT_CONST(TEntities, it, _entities) {
			if((*it)->getName() == name) {
				return *it;
			}
		}

		return NULL;
	}

	CEntity *CLevel::getEntityByID(TEntityID id) const {
		FOR_IT_CONST(TEntities, it, _entities) {
			if((*it)->getID() == id) {
				return *it;
			}
		}

		return NULL;
	}

	void CLevel::destroyAllEntities() {
		FOR_IT_CONST(TEntities, it, _entities) {
			delete *it;
		}

		_entities.clear();
	}

}