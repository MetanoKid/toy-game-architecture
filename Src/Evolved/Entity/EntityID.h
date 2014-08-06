#ifndef Evolved_EntityID_H
#define Evolved_EntityID_H

namespace Evolved {

	/**
	Alias for the type of entity's ID.
	*/
	typedef unsigned int TEntityID;

	/**
	Entity ID's are generated incrementally and won't be recycled when entities are
	destroyed. By calling its nextID() method we get the next available ID for an
	entity, which is guaranteed to be unique as the same ID won't be returned again.
	*/
	class CEntityID {
	private:
		/**
		Some constants for the structure.
		*/
		enum {
			FIRST_ID = 0x00000000,
			LAST_ID = 0xFFFFFFFF
		};

		/**
		Next available ID.
		*/
		static TEntityID _nextID;

	public:
		/**
		Gets the next available ID.
		*/
		static TEntityID nextID();
	};

}

#endif