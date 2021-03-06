#ifndef EvolvedPlus_Application_H
#define EvolvedPlus_Application_H

namespace EvolvedPlus {

	/**
	Forward declarations.
	*/
	class CLevel;

	/**
	This class represents the entry point of the application.
	It manages the life cycle of the application, creating, initializing, running and
	killing it when necessary.
	*/
	class CApplication {
	protected:
		/**
		Current level used in the application.
		*/
		EvolvedPlus::CLevel *_currentLevel;

		/**
		The current and unique instance of the singleton.
		*/
		static CApplication *_instance;

		/**
		Basic constructor, private as a part of the singleton pattern.
		*/
		CApplication();

		/**
		Basic destructor.
		We can only destruct it from inside, so it's private.
		*/
		virtual ~CApplication();

		/**
		In order to prevent accidental (or intentional) copying of the singleton instance,
		we declare the copy constructor as private so a compile-time error is shown.
		*/
		CApplication(const CApplication &factory);

		/**
		In order to prevent accidental (or intentional) copying of the singleton instance,
		we declare the assignment operator as private so a compile-time error is shown.
		*/
		CApplication &operator=(const CApplication &factory);

	public:
		/**
		Initializes the application including every subsystem.
		*/
		virtual bool initialize();

		/**
		Runs the application until exit is requested.
		*/
		virtual void run();

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
		static CApplication &getInstance();
	};

}

#endif