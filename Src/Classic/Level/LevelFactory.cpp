#include "LevelFactory.h"

#include <cassert>
#include <fstream>

#include "Level.h"
#include "LevelEntry.h"

namespace Classic {

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

			printf("Just processed '%s' which is a '%s'\n\n", levelEntry.name.c_str(), levelEntry.type.c_str());
		}

		return level;
	}
}