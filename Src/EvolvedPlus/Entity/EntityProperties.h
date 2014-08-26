#ifndef EvolvedPlus_EntityProperties_H
#define EvolvedPlus_EntityProperties_H

#include <set>
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
		friend class CEntityFactory;

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

			// do we have the component it's been asked for?
			if(it == _data.componentData.end()) {
				return _parent && _parent->get<T>(component, propertyName, outValue);
			}

			// we've got the component and some of its data, do we have the data that's been asked for?
			if(it->second.get<T>(propertyName, outValue)) {
				return true;
			}

			// we've got the component and the data, but the data that's been asked for might be in the parent
			if(_parent) {
				return _parent->get<T>(component, propertyName, outValue);
			}

			return NULL;
		}

		/**
		Gets the type of the entity for these properties.
		*/
		const std::string &getType() const;

		/**
		Alias for a set of unique component names.
		*/
		typedef std::set<std::string> TComponentNames;

		/**
		Gets the name of the components for this entry, even walking through parents if necessary.
		*/
		TComponentNames getComponentNames() const;
	};

}

#endif