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
		std::string fileName;

		if(!CConfig::getInstance().get<std::string>("archetypes_evolved_plus", fileName)) {
			assert(false && "Couldn't find property archetypes in the config file.");
		}

		// does the file exist?
		std::ifstream in(fileName);
		assert(in && "Archetypes file couldn't be opened");

		// let's process the file
		while(!in.eof()) {
			CLevelEntry levelEntry;
			in >> levelEntry;

			// don't allow archetype duplicates, and get where it should be inserted
			TArchetypes::const_iterator it = _archetypes.lower_bound(levelEntry.name);
			assert(it == _archetypes.end() && "Duplicate archetype name.");

			CEntityProperties archetypeData;
			archetypeData.setData(levelEntry);

			_archetypes.insert(it, TArchetypes::value_type(levelEntry.name, archetypeData));
		}

		// now we've processed every entry in the archetypes file, we have to link them
		FOR_IT(TArchetypes, it, _archetypes) {
			// did it declare an archetype?
			CEntityProperties *properties = &it->second;

			if(!properties->_data.archetype.empty()) {
				properties->setParent(getArchetype(properties->_data.archetype));
			}
		}
	}

	CEntityProperties *CEntityFactory::getArchetype(const std::string &name) {
		TArchetypes::iterator it = _archetypes.find(name);
		assert(it != _archetypes.end() && "Archetype doesn't exist.");

		return &it->second;
	}

}