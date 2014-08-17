#ifndef EvolvedPlus_LevelEntry_H
#define EvolvedPlus_LevelEntry_H

#include <string>
#include <sstream>
#include <cassert>
#include <map>

#include "EvolvedPlus/Properties.h"

namespace EvolvedPlus {

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
		Alias for the map to match components and data.
		*/
		typedef std::map<std::string, CProperties> TComponentData;

		/**
		Data for every component.
		*/
		TComponentData componentData;

		/**
		Processes an entry in the level file into a data structure.
		Every entry in the file has this structure:

		<Entity name> : <Entity type>
			<Component name>
				<Property name> <Property value>
				<Property name> <Property value>

		For example:

		EntityName : EntityType
			Light
				type Directional
			Perception
				type Soldier
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

			// start processing component data
			std::string componentName;
			std::string propertyName;
			std::string propertyValue;
			CProperties properties;
			bool parsingComponentName = true;
			std::getline(is, aux, '\n');

			while(!aux.empty()) {
				if(parsingComponentName) {
					// we're expecting a name, so we're expecting a single tab
					assert(aux.find('\t') == 0 && "Every component name must start with a tab.");

					// get the name of the component
					iss.str(aux);
					iss.clear();
					iss >> componentName;

					// ensure we haven't got a duplicate component
					CLevelEntry::TComponentData::const_iterator it = entry.componentData.find(componentName);
					assert(it == entry.componentData.end() && "Duplicated component name entry.");

					parsingComponentName = false;
				} else {
					int position = aux.find_last_of('\t');

					switch(position) {
						case 0:
							// we've finished a component and got another one, so insert it into the map and continue
							entry.componentData[componentName] = properties;
							properties = CProperties();

							parsingComponentName = true;
							continue;

						case 1:
							// we're still processing properties, so token its name and value
							iss.str(aux);
							iss.clear();

							iss >> propertyName;
							std::getline(iss, propertyValue, '\n');
							properties.put(propertyName, trim(propertyValue));
							break;

						default:
							assert(false && "Expecting a component name or property and found a wrong entry.");
							break;
					}
				}

				// was that the last line?
				if(is.eof()) {
					break;
				}

				// get next line and continue parsing
				std::getline(is, aux, '\n');
			}

			entry.componentData[componentName] = properties;

			return is;
		}
	};

}

#endif