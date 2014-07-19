#include <cassert>
#include <fstream>

#include "EntityFactory.h"
#include "Blueprint.h"

namespace Classic {

#define BLUEPRINTS_FILE_PATH "blueprints.txt"

	/**
	Initialize the instance so it doesn't exist when the architecture starts.
	*/
	CEntityFactory *CEntityFactory::_instance = NULL;

	CEntityFactory::CEntityFactory() {
		// open blueprints file and load it into our structure
		std::ifstream in(BLUEPRINTS_FILE_PATH);

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

}