#include <cassert>
#include <fstream>

#include "EntityFactory.h"

#include "EntityID.h"
#include "EvolvedPlus/Components/Component.h"
#include "EvolvedPlus/Components/ComponentFactory.h"
#include "EvolvedPlus/Level/Level.h"
#include "EvolvedPlus/Level/LevelEntry.h"
#include "EvolvedPlus/Config/Config.h"
#include "Application/Macros.h"

namespace EvolvedPlus {

	CEntityFactory *CEntityFactory::_instance = NULL;

	CEntityFactory::CEntityFactory() {

	}

	CEntityFactory::~CEntityFactory() {

	}

	CEntityFactory::CEntityFactory(const CEntityFactory &factory) {
		_instance = factory._instance;
	}

	CEntityFactory &CEntityFactory::operator=(const CEntityFactory &factory) {
		if(this != &factory) {
			_instance = factory._instance;
		}

		return *this;
	}

	void CEntityFactory::release() {
		if(_instance) {
			delete _instance;
		}

		_instance = NULL;
	}

	CEntityFactory &CEntityFactory::getInstance() {
		if(!_instance) {
			_instance = new CEntityFactory();
			_instance->parseArchetypes();
		}

		return *_instance;
	}

	CEntityData CEntityFactory::build(const TEntityID &id, const CLevelEntry &levelEntry) const {
		// create the entity data, which won't have any component or anything yet
		CEntityData entity;

		// build its components
		FOR_IT_CONST(CLevelEntry::TComponentData, it, levelEntry.componentData) {
			IComponent *component = CComponentFactory::getInstance().build(it->first);
			entity.components.push_back(component);

			component->setEntity(id);
		}

		// and return it
		return entity;
	}

	void CEntityFactory::parseArchetypes() {

	}

	CEntityProperties *CEntityFactory::getArchetype(const std::string &name) const {
		return NULL;
	}

}