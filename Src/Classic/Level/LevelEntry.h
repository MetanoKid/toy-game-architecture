#ifndef Classic_LevelEntry_H
#define Classic_LevelEntry_H

#include <string>
#include <sstream>
#include <cassert>

#include "LevelData.h"

namespace Classic {

	/**
	Trims a string from both start and end
	*/
	std::string trim(const std::string &str) {
		int first = str.find_first_not_of(' ');
		int last = str.find_last_not_of(' ');
		return str.substr(first, last - first + 1);
	}

	/**
	Every level has several entries which describe entities and their data.
	This struct represents one of those entries.
	*/
	struct CLevelEntry {
		/**
		Name of the entity in the entry.
		*/
		std::string name;

		/**
		Type of the entity in the entry.
		*/
		std::string type;

		/**
		Data associated to this entry.
		*/
		CLevelData properties;

		/**
		Processes an entry in the level file into a data structure.
		Every entry in the file has this structure:

		<Entity name> : <Entity type>
			<Property name> <Property value>
			<Property name> <Property value>

		For example:

		Player : Player
			life 100
			model Player.fbx
		*/
		friend std::istream &operator>>(std::istream &is, CLevelEntry &entry) {
			std::string aux;

			// get the first line, it has the name and the type of the entity
			std::getline(is, aux, '\n');

			// create a stream to process the line
			std::istringstream iss(aux);

			// this first entry line is "<Entity name> : <Entity type>"
			std::string item;
			std::vector<std::string> items;

			while(std::getline(iss, item, ':')) {
				if(!item.empty()) {
					items.push_back(item);
				}
			}

			// ensure we've got exactly what we expect
			assert(items.size() == 2 && "Level entry header (name : type) incorrect.");

			// and set them
			entry.name = trim(items[0]);
			entry.type = trim(items[1]);

			// we'll use these variables to extract properties data
			std::string propertyName;
			std::string propertyValue;

			// start processing properties
			std::getline(is, aux, '\n');

			while(!aux.empty()) {
				assert(aux.find('\t') == 0 && "Every property line must start with a tab.");

				// reuse our string stream using the line
				iss.str(aux);
				iss.clear();

				iss >> propertyName;
				std::getline(iss, propertyValue, '\n');

				// add the property to the struct
				entry.properties.put(propertyName, trim(propertyValue));

				// was this the last line?
				if(is.eof()) {
					break;
				}

				// get next line to continue processing
				std::getline(is, aux, '\n');
			}

			return is;
		}
	};

}

#endif