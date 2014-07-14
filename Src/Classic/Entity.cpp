#include "Entity.h"
#include "Application/Macros.h"

namespace Classic {

	CEntity::CEntity(TEntityID id) : _id(id), _name(""), _type(""), _active(false), _level(NULL) {

	}

	CEntity::~CEntity() {
		destroyComponents();
	}

	bool CEntity::spawn(const std::string &entityName, CLevelData *data, CLevel *level) {

	}

	bool CEntity::activate() {
		// by default, we think we'll be active
		_active = true;

		// activate every component
		FOR(TComponents, it, _components) {

		}

		return _active;
	}

	void CEntity::deactivate() {
		_active = false;
	}

	void CEntity::tick(float secs) {

	}

	void CEntity::addComponent(IComponent *component) {

	}

	void CEntity::removeComponent(IComponent *component) {

	}

	void CEntity::destroyComponents() {

	}

	bool CEntity::sendMessage(CMessage *message, IComponent *emitter = 0) {

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

	const std::string &CEntity::getType() const {
		return _type;
	}

	bool CEntity::isActive() const {
		return _active;
	}

}