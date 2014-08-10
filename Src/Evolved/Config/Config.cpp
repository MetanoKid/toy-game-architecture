#include "Config.h"

#include <fstream>

namespace Evolved {

#define CONFIG_FILE "Configuration.txt"

	CConfig *CConfig::_instance = NULL;

	CConfig::CConfig() {
		parseConfigFile(CONFIG_FILE);
	}

	CConfig::~CConfig() {

	}

	CConfig::CConfig(const CConfig &factory) {
		_instance = factory._instance;
	}

	CConfig &CConfig::operator=(const CConfig &factory) {
		if(this != &factory) {
			_instance = factory._instance;
		}

		return *this;
	}

	void CConfig::release() {
		if(_instance) {
			delete _instance;
		}

		_instance = NULL;
	}

	CConfig &CConfig::getInstance() {
		if(!_instance) {
			_instance = new CConfig();
		}

		return *_instance;
	}

	void CConfig::parseConfigFile(const std::string &filePath) {
		// does the file exist?
		std::ifstream in(filePath);
		assert(in && "Config file couldn't be opened.");

		// load config properties
		in >> _properties;
	}

}