#include "Level.h"

#include "Application/Macros.h"
#include "Classic/Entity/Entity.h"

namespace Classic {

	CLevel::CLevel() {

	}

	CLevel::~CLevel() {
		destroyAllEntities();
	}

	bool CLevel::activate() {
		FOR_IT_CONST(TEntities, it, _entities) {
			if(!(*it)->activate()) {
				return false;
			}
		}

		return true;
	}

	void CLevel::deactivate() {
		FOR_IT_CONST(TEntities, it, _entities) {
			(*it)->deactivate();
		}
	}

	void CLevel::tick(float secs) {
		FOR_IT_CONST(TEntities, it, _entities) {
			(*it)->tick(secs);
		}
	}

	bool CLevel::addEntity(CEntity *entity) {
		TEntities::const_iterator it = std::find(_entities.begin(), _entities.end(), entity);

		if(it == _entities.end()) {
			_entities.push_back(entity);
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