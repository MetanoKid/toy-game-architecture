#include "LevelFactory.h"

#include <cassert>
#include <fstream>

#include "Level.h"
#include "LevelEntry.h"
#include "EvolvedPlus/Entity/EntityFactory.h"
#include "Application/Macros.h"

namespace EvolvedPlus {

	CLevelFactory *CLevelFactory::_instance = NULL;

	CLevelFactory::CLevelFactory() {

	}

	CLevelFactory::~CLevelFactory() {

	}

	CLevelFactory::CLevelFactory(const CLevelFactory &factory) {
		_instance = factory._instance;
	}

	CLevelFactory &CLevelFactory::operator=(const CLevelFactory &factory) {
		if(this != &factory) {
			_instance = factory._instance;
		}

		return *this;
	}

	void CLevelFactory::release() {
		if(_instance) {
			delete _instance;
		}

		_instance = NULL;
	}

	CLevelFactory &CLevelFactory::getInstance() {
		if(!_instance) {
			_instance = new CLevelFactory();
		}

		return *_instance;
	}

	CLevel *CLevelFactory::build(const std::string &fileName) const {
		// does the file exist?
		std::ifstream in(fileName);
		assert(in && "Level file couldn't be opened.");

		// create the level we'll be building and returning
		CLevel *level = new CLevel();

		// let's start processing
		while(!in.eof()) {
			CLevelEntry levelEntry;
			in >> levelEntry;

			// try to find if it's got an archetype or a type
			CEntityProperties properties;
			properties.setData(levelEntry);

			if(!levelEntry.archetype.empty()) {
				properties.setParent(CEntityFactory::getInstance().getArchetype(levelEntry.archetype));
			}

			// now that we've read the entity data from the level, create a new
			// entity without properties, just structure (components)
			// this is part of the two-step initialization: first structure then data
			TEntityID entityID = CEntityID::nextID();
			CEntityData entity(CEntityFactory::getInstance().build(entityID, properties));

			// now set some properties
			entity.name = levelEntry.name;
			entity.type = properties.getType();
			entity.data = properties;

			// store data for second step when adding to the level
			level->addEntity(entityID, entity);
		}

		return level;
	}
}