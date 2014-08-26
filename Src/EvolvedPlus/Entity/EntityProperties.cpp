#include "EntityProperties.h"
#include "Application/Macros.h"

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

	CEntityProperties::TComponentNames CEntityProperties::getComponentNames() const {
		TComponentNames names;

		FOR_IT_CONST(CLevelEntry::TComponentData, it, _data.componentData) {
			names.insert(it->first);
		}

		if(_parent) {
			TComponentNames parentComponentNames = _parent->getComponentNames();
			names.insert(parentComponentNames.begin(), parentComponentNames.end());
		}

		return names;
	}

}