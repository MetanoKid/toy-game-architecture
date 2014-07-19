#ifndef Classic_EntityFactory_H
#define Classic_EntityFactory_H

namespace Classic {

	/**
	The task of creating and destroying entities is delegated to this factory.
	Entities have two important concepts: they have a type and they have properties.
	Types are defined as blueprints (which components compose the entity) and those
	blueprints are defined in a file. The factory will process blueprints on initialization
	and will use them when building entities.
	Their properties are defined in a level file, which are processed and passed to
	this factory to build those entities.

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
	};

}

#endif