#include <cassert>
#include <fstream>

#include "EntityFactory.h"

#include "Blueprint.h"
#include "EntityID.h"
#include "Evolved/Components/Component.h"
#include "Evolved/Components/ComponentFactory.h"
#include "Evolved/Level/Level.h"
#include "Evolved/Config/Config.h"
#include "Application/Macros.h"

namespace Evolved {

	CEntityFactory *CEntityFactory::_instance = NULL;

	CEntityFactory::CEntityFactory() {
		// open blueprints file and load it into our structure
		std::string fileName;

		if(!CConfig::getInstance().get<std::string>("blueprints", fileName)) {
			assert(false && "Couldn't find property blueprints in the config file.");
		}

		std::ifstream in(fileName);

		assert(in && "Blueprints file could not be opened.");

		while(!in.eof()) {
			// read a blueprint
			CBlueprint blueprint;
			in >> blueprint;

			// was that an empty line?
			if(!blueprint.type.empty()) {
				// check for duplicates
				assert(_blueprints.count(blueprint.type) == 0 && "Duplicate blueprint");

				// add the blueprint to our map
				_blueprints[blueprint.type] = blueprint;
			}
		}
	}

	CEntityFactory::~CEntityFactory() {
		// unload blueprints
		_blueprints.clear();
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
		}

		return *_instance;
	}

	CEntityData CEntityFactory::build(const TEntityID &id, const std::string &entityType) const {
		// do we have the type?
		assert(_blueprints.count(entityType) != 0 && "Blueprint couldn't be found.");

		// create the entity data, which won't have any component or anything yet
		CEntityData entity;

		// build its components
		CBlueprint blueprint = _blueprints.find(entityType)->second;
		FOR_IT_CONST(CBlueprint::TComponentNames, it, blueprint.components) {
			IComponent *component = CComponentFactory::getInstance().build(*it);
			entity.components.push_back(component);

			component->setEntity(id);
		}

		// and return it
		return entity;
	}

}