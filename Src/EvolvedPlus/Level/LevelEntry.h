#ifndef EvolvedPlus_LevelEntry_H
#define EvolvedPlus_LevelEntry_H

#include <string>
#include <sstream>
#include <cassert>
#include <map>
#include <vector>

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
		Type of the entity in the entry, if any.
		*/
		std::string type;

		/**
		Name of the archetype of this entry, if any.
		*/
		std::string archetype;

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

		Or this structure:

		<Entity name> : [<Entity archetype>]
			<Component name>
				<Property name> <Property value>
				<Property name> <Property value>

		For example:

		EntityName : EntityType
			Light
				type Directional
			Perception
				type Soldier

		Or:

		EntityName : [ArchetypeName]
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

			// this first entry line is "<Entity name> : <Entity type>" or "<Entity name> : [<Archetype>]"
			std::string item;
			std::vector<std::string> items;

			while(std::getline(iss, item, ':')) {
				if(!item.empty()) {
					items.push_back(item);
				}
			}

			// ensure we've got exactly what we expect
			assert(items.size() == 2 && "Level entry header incorrect.");

			// and set them
			entry.name = trim(items[0]);
			entry.extractTypeArchetypeFrom(items[1]);

			// start processing component data
			std::string componentName;
			std::string propertyName;
			std::string propertyValue;
			CProperties properties;
			bool parsingComponentName = true;

			// address the scenario in which the last item in a level file has no components defined
			// instead, it just has its archetype (or even type, but it could be an useless entity)
			if(is.eof()) {
				return is;
			}

			// start parsing components
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

			// insert data which we were building, in case there's any
			if(!componentName.empty()) {
				entry.componentData[componentName] = properties;
			}

			return is;
		}

	private:
		void extractTypeArchetypeFrom(const std::string &data) {
			int openingBracketPos = data.find_first_of('[');
			int closingBracketPos = data.find_first_of(']');

			// is it the type?
			if(openingBracketPos == -1 && closingBracketPos == -1) {
				type = trim(data);
				return;
			}

			// it's the archetype
			assert(openingBracketPos != -1 && closingBracketPos != -1 &&
			       "Archetype name must be enclosed between '[' and ']'.");
			assert(openingBracketPos < closingBracketPos && "Archetype name must be enclosed between '[' and ']'.");
			assert(std::count(data.begin(), data.end(), '[') == 1 &&
			       std::count(data.begin(), data.end(), ']') == 1 &&
			       "Archetype name can't have '[' or ']' in its name.");

			openingBracketPos++;
			archetype = trim(data.substr(openingBracketPos, closingBracketPos - openingBracketPos));
		}
	};

}

#endif