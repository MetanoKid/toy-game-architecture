#ifndef EvolvedPlus_EntityFactory_H
#define EvolvedPlus_EntityFactory_H

#include <map>
#include <vector>

#include "EntityID.h"
#include "EntityData.h"
#include "EvolvedPlus/Level/LevelEntry.h"

namespace EvolvedPlus {

	/**
	The task of creating and destroying entities is delegated to this factory.
	Entities have two important concepts: they have a name and they have components.
	Components have some data associated to them so they can be configured so they perform
	their behaviors. That data is in fact a set of properties defined in a level file,
	which are processed and passed to this factory to build entities.
	Before, we had blueprints, which defined which components formed an entity. Now,
	blueprints don't exist and components are inferred from the level file.

	It's implemented as a one-step initialization singleton, which is protected against
	accidental or intentional copies.
	*/
	class CEntityFactory {
	private:
		/**
		The current and unique instance of the singleton.
		*/
		static CEntityFactory *_instance;

		/**
		Basic constructor, private as a part of the singleton pattern.
		*/
		CEntityFactory();

		/**
		Basic destructor.
		We can only destruct it from inside, so it's private.
		*/
		~CEntityFactory();

		/**
		In order to prevent accidental (or intentional) copying of the singleton instance,
		we declare the copy constructor as private so a compile-time error is shown.
		*/
		CEntityFactory(const CEntityFactory &factory);

		/**
		In order to prevent accidental (or intentional) copying of the singleton instance,
		we declare the assignment operator as private so a compile-time error is shown.
		*/
		CEntityFactory &operator=(const CEntityFactory &factory);

	public:
		/**
		When the singleton won't be used anymore, we can call this method to destroy the
		current instance. This is the only way of destroying it and not calling it would
		leak it.
		*/
		static void release();

		/**
		Gets the instance of this factory.
		It's a singleton, and by returning instead of a pointer we are subtly declaring
		three characteristics:
		    - It won't be NULL: if it was a pointer, and even if we did our work
			  initializing it, it could be NULL conceptually.
			- It can't be changed: a pointer could be pointed somewhere else.
			- It can't be deleted from outside code: pointers could.
		*/
		static CEntityFactory &getInstance();

		/**
		Creates an entity given a type. That will create the basic data, instantiate
		components for that entity and set it up.
		*/
		CEntityData build(const TEntityID &id, const CLevelEntry &levelEntry) const;
	};

}

#endif