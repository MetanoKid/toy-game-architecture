#include <stdio.h>
#include <cassert>

#include "EntityFactory.h"

namespace Classic {

	/**
	Initialize the instance so it doesn't exist when the architecture starts.
	*/
	CEntityFactory *CEntityFactory::_instance = NULL;

	CEntityFactory::CEntityFactory() {
		// open blueprints file and load it
	}

	CEntityFactory::~CEntityFactory() {
		// unload blueprints
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