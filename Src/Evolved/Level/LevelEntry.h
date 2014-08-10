#ifndef Evolved_LevelEntry_H
#define Evolved_LevelEntry_H

#include <string>
#include <sstream>
#include <cassert>

#include "Evolved/Properties.h"

namespace Evolved {

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
		CProperties properties;

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

			// get properties data
			entry.properties.setRequiredTabs(1);
			is >> entry.properties;

			return is;
		}
	};

}

#endif