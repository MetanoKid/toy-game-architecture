#include "ComponentFactory.h"

#include <cassert>

#include "Application/Macros.h"

namespace Evolved {

	CComponentFactory *CComponentFactory::_instance = NULL;

	CComponentFactory::CComponentFactory() {

	}

	CComponentFactory::~CComponentFactory() {
		_components.clear();
	}

	CComponentFactory::CComponentFactory(const CComponentFactory &factory) {
		_instance = factory._instance;
	}

	CComponentFactory &CComponentFactory::operator=(const CComponentFactory &factory) {
		if(this != &factory) {
			_instance = factory._instance;
		}

		return *this;
	}

	void CComponentFactory::release() {
		if(_instance) {
			delete _instance;
		}

		_instance = NULL;
	}

	CComponentFactory &CComponentFactory::getInstance() {
		if(!_instance) {
			_instance = new CComponentFactory();
		}

		return *_instance;
	}

	void CComponentFactory::add(const std::string &name, ComponentInstantiator instantiator) {
		/**
		Each time we include a compilation unit of a component, it will be registered into this factory.
		We'll just override its value since it's cheaper than looking for it and then doing nothing.
		*/
		_components[name] = instantiator;
	}

	IComponent *CComponentFactory::build(const std::string &name) const {
		// do we have the component?
		assert(_components.count(name) != 0 && "Trying to build an unregistered component.");

		// build the component and return it (we know it exists or else the assert would've failed)
		return _components.find(name)->second();
	}

}