#include "EntityProperties.h"

namespace EvolvedPlus {

	CEntityProperties::CEntityProperties() : _parent(NULL) {

	}

	CEntityProperties::~CEntityProperties() {

	}

	/**
	Sets the LevelEntry data for this entity.
	*/
	void CEntityProperties::setData(CLevelEntry data) {
		_data = data;
	}

	/**
	Sets the parent archetype.
	*/
	void CEntityProperties::setParent(CEntityProperties *parent) {
		_parent = parent;
	}

	/**
	Gets the type of the entity for these properties.
	*/
	const std::string &CEntityProperties::getType() const {
		// if it doesn't have a type it must have a parent
		return _data.type.empty() ? _parent->getType() : _data.type;
	}

}