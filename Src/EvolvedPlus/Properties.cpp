#include "Properties.h"

namespace EvolvedPlus {

	CProperties::CProperties(unsigned int requiredTabs) : _requiredTabs(requiredTabs) {

	}

	CProperties::~CProperties() {
		_properties.clear();
	}

	void CProperties::put(const std::string &propertyName, const std::string &propertyValue) {
		assert(_properties.count(propertyName) == 0 && "Duplicated property.");

		_properties[propertyName] = propertyValue;
	}

	void CProperties::setRequiredTabs(unsigned int requiredTabs) {
		_requiredTabs = requiredTabs;
	}

}