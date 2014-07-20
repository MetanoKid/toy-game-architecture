#ifndef Classic_LevelFactory_H
#define Classic_LevelFactory_H

#include <string>

namespace Classic {

	// forward declarations
	class CLevel;

	/**
	Whenever a Level needs to be built we'll be using this factory. Every level has its
	initialization divided into two steps, just like entities their components. Within the
	first step the level is created and every instance is built and added into it. That just
	provides the basic structure for every entity (which components are associated for each, etc).
	Then, the second step involves initializing every entity and component with data. That data
	comes directly from the level, which was processed during the first step.
	*/
	class CLevelFactory {
	private:
		/**
		The current and unique instance of the singleton.
		*/
		static CLevelFactory *_instance;

		/**
		Basic constructor, private as a part of the singleton pattern.
		*/
		CLevelFactory();

		/**
		Basic destructor.
		We can only destruct it from inside, so it's private.
		*/
		~CLevelFactory();

		/**
		In order to prevent accidental (or intentional) copying of the singleton instance,
		we declare the copy constructor as private so a compile-time error is shown.
		*/
		CLevelFactory(const CLevelFactory &factory);

		/**
		In order to prevent accidental (or intentional) copying of the singleton instance,
		we declare the assignment operator as private so a compile-time error is shown.
		*/
		CLevelFactory &operator=(const CLevelFactory &factory);

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
		static CLevelFactory &getInstance();

		/**
		Creates a level given a file name, building any entity that exists in the level.
		Every built entity is built but not initialized
		*/
		CLevel *build(const std::string &fileName) const;
	};

}

#endif