#include "LevelData.h"

namespace Classic {

	CLevelData::CLevelData() {

	}

	CLevelData::~CLevelData() {
		_properties.clear();
	}

	void CLevelData::put(const std::string &propertyName, const std::string &propertyValue) {
		assert(_properties.count(propertyName) == 0 && "Duplicated property.");

		_properties[propertyName] = propertyValue;
	}

}