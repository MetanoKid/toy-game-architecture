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
		CLevelEntry::TComponentData _data;

	public:
		/**
		Default constructor.
		*/
		CEntityProperties() {

		}

		/**
		Basic destructor.
		*/
		~CEntityProperties() {

		}

		void setData(CLevelEntry::TComponentData data) {
			_data = data;
		}

		/**
		Gets a property for a given component, if it exists.
		*/
		template <typename T>
		bool get(IComponent *component, const std::string &propertyName, T &outValue) const {
			CLevelEntry::TComponentData::const_iterator it = _data.find(component->getName());

			if(it == _data.end()) {
				return false;
			}

			const CProperties *properties = &it->second;
			return it->second.get<T>(propertyName, outValue);
		}
	};

}

#endif