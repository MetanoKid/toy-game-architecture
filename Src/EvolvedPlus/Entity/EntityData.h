#ifndef EvolvedPlus_EntityData_H
#define EvolvedPlus_EntityData_H

#include <string>
#include <vector>

#include "EntityProperties.h"

namespace EvolvedPlus {

	/**
	Forward declarations.
	*/
	class IComponent;

	/**
	In this approach, entities are just an identifier and some data associated
	to it instead of being a full abstraction with behavior.
	This data structure packs that data into a more usable concept.
	*/
	struct CEntityData {
		/**
		Entity's name.
		*/
		std::string name;

		/**
		Entity's type.
		*/
		std::string type;

		/**
		Is this entity active?
		*/
		bool active;

		/**
		Entity's components.
		*/
		std::vector<IComponent *> components;

		/**
		Inactive components for this entity.
		*/
		std::vector<IComponent *> disabledComponents;

		/**
		Data defined in the level for this entity.
		*/
		CEntityProperties data;
	};
}

#endif