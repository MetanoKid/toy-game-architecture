#ifndef Classic_Blueprint_H
#define Classic_Blueprint_H

#include <string>
#include <vector>
#include <sstream>

namespace Classic {

	/**
	A blueprint defines entity types and the components that are associated to those
	types. An istream operator is provided so reading from any stream is performed
	transparently.
	*/
	struct CBlueprint {
		/**
		The type of the entity we're defining, any name is valid and will be the one
		used in the level to determine the type of the entity.
		*/
		std::string type;

		/**
		Alias for a component names list.
		*/
		typedef std::vector<std::string> TComponentNames;

		/**
		List of component names associated to this entity type. When instanciating
		an entity of this type, components with these names will be instantiated as well.
		*/
		TComponentNames components;

		/**
		Processes an entry in the blueprints file into a blueprint.
		Every entry in the file has this structure:

		<EntityType> <List of component names separated by spaces>

		For example:
		Player CAvatarController CPerception CAnimatedGraphics
		*/
		friend std::istream &operator>>(std::istream &is, CBlueprint &blueprint) {
			// get the type, which is the first item in the entry
			is >> blueprint.type;

			// now get the rest of the entry in a stringstream so we deal with it
			std::string aux;
			std::getline(is, aux, '\n');
			std::istringstream componentNames(aux);

			// let's process them
			while(!componentNames.eof()) {
				aux.clear();
				componentNames >> aux;

				// some protection
				if(!aux.empty()) {
					// push it
					blueprint.components.push_back(aux);
				}
			}

			return is;
		}
	};

}

#endif