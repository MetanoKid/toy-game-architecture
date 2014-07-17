#include "Entity.h"
#include "Classic/Components/Component.h"
#include "Application/Macros.h"

namespace Classic {

	CEntity::CEntity(TEntityID id) : _id(id), _name(""), _type(""), _active(false), _level(NULL) {

	}

	CEntity::~CEntity() {
		destroyComponents();
	}

	bool CEntity::spawn(const std::string &entityName, CLevelData *data, CLevel *level) {
		// keep some entity-level information, like name, type or level
		_name = entityName;
		_level = level;
		// _type = data->get<string>("type");

		// now, spawn components
		FOR_IT_CONST(TComponents, it, _components) {
			// if any component's spawn fails, stop right away
			if(!(*it)->spawn(entityName, data, level)) {
				return false;
			}
		}

		return true;
	}

	bool CEntity::activate() {
		// by default, we think we'll be active
		_active = true;

		// activate every component
		FOR_IT_CONST(TComponents, it, _components) {
			_active = (*it)->activate() || _active;
		}

		return _active;
	}

	void CEntity::deactivate() {
		_active = false;

		FOR_IT_CONST(TComponents, it, _components) {
			(*it)->deactivate();
		}
	}

	void CEntity::tick(float secs) {
		FOR_IT_CONST(TComponents, it, _components) {
			(*it)->doTick(secs);
		}
	}

	void CEntity::addComponent(IComponent *component) {
		_components.push_back(component);
		component->setEntity(this);
	}

	void CEntity::removeComponent(IComponent *component) {
		TComponents::const_iterator it = std::find(_components.begin(), _components.end(), component);

		if(it != _components.end()) {
			_components.erase(it);
			component->setEntity(NULL);
		}
	}

	void CEntity::destroyComponents() {
		FOR_IT_CONST(TComponents, it, _components) {
			delete(*it);
		}

		_components.clear();
	}

	bool CEntity::sendMessage(Messages::CMessage *message, IComponent *emitter) {
		// we assume there are no entity-level messages, just component-level ones
		// if we had, we'd have to process those messages here, before handing them
		// in to components

		// due to the nature of the messages in this architecture, we'll have to
		// check if the message was enqueued by any component
		bool enqueued = false;

		FOR_IT_CONST(TComponents, it, _components) {
			if(*it != emitter) {
				enqueued = (*it)->enqueueMessage(message) || enqueued;
			}
		}

		// if no component accepted the message, then we are safe to delete it
		if(!enqueued) {
			delete message;
		}

		return enqueued;
	}

	CLevel *CEntity::getLevel() const {
		return _level;
	}

	const std::string &CEntity::getName() const {
		return _name;
	}

	void CEntity::setName(const std::string &name) {
		_name = name;
	}

	TEntityID CEntity::getID() const {
		return _id;
	}

	const std::string &CEntity::getType() const {
		return _type;
	}

	bool CEntity::isActive() const {
		return _active;
	}

}