#ifndef EvolvedPlus_EntityProperties_H
#define EvolvedPlus_EntityProperties_H

#include "EvolvedPlus/Level/LevelEntry.h"

namespace EvolvedPlus {

	/**
	Forward declarations.
	*/
	class IComponent;

	/**
	This class represents the data passed to components when they're spawned.
	It contains all the data extracted from the level file, and provides an
	entry point to obtain properties for components separatedly.
	*/
	class CEntityProperties {
	private:
		/**
		Data related to an entity.
		*/
		CLevelEntry _data;

		/**
		Parent archetype, if any.
		*/
		CEntityProperties *_parent;

	public:
		/**
		Default constructor.
		*/
		CEntityProperties();

		/**
		Basic destructor.
		*/
		~CEntityProperties();

		/**
		Sets the LevelEntry data for this entity.
		*/
		void setData(CLevelEntry data);

		/**
		Sets the parent archetype.
		*/
		void setParent(CEntityProperties *parent);

		/**
		Gets a property for a given component, if it exists.
		*/
		template <typename T>
		bool get(IComponent *component, const std::string &propertyName, T &outValue) const {
			CLevelEntry::TComponentData::const_iterator it = _data.componentData.find(component->getName());

			if(it == _data.componentData.end()) {
				return false;
			}

			return it->second.get<T>(propertyName, outValue) ||
			       (_parent && _parent->get<T>(component, propertyName, outValue));
		}

		/**
		Gets the type of the entity for these properties.
		*/
		const std::string &getType() const;
	};

}

#endif