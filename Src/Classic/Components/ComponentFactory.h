#ifndef Classic_ComponentFactory_H
#define Classic_ComponentFactory_H

#include <string>
#include <map>

namespace Classic {

	// forward declarations
	class IComponent;

	/**
	Within the process of building entities we've got to build their components. This
	factory will be the one in charge of doing so.
	Implemented using a one-step initialization singleton, it will store a map of component
	names and function pointers to instantiate each one of them. That means every component
	must declare a way of instantiating them, with no parameters.
	This concept matches perfectly with our entity/component two-step initialization
	philosophy: we build the entity/component with no parameters and then we initialize it
	with data coming from the level.
	*/
	class CComponentFactory {
	private:
		/**
		The current and unique instance of the singleton.
		*/
		static CComponentFactory *_instance;

		/**
		Basic constructor, private as a part of the singleton pattern.
		*/
		CComponentFactory();

		/**
		Basic destructor.
		We can only destruct it from inside, so it's private.
		*/
		~CComponentFactory();

		/**
		In order to prevent accidental (or intentional) copying of the singleton instance,
		we declare the copy constructor as private so a compile-time error is shown.
		*/
		CComponentFactory(const CComponentFactory &factory);

		/**
		In order to prevent accidental (or intentional) copying of the singleton instance,
		we declare the assignment operator as private so a compile-time error is shown.
		*/
		CComponentFactory &operator=(const CComponentFactory &factory);

		/**
		Alias for a function pointer which creates a component.
		Those functions will be static functions which exist within the components.
		*/
		typedef IComponent *(*ComponentInstantiator)();

		/**
		Alias for our structure to store component constructors.
		*/
		typedef std::map<std::string, ComponentInstantiator> TComponents;

		/**
		Structure to store component names and functions to create each one of them.
		*/
		TComponents _components;

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
		static CComponentFactory &getInstance();

		/**
		Adds a component to the internal structure.
		*/
		void add(const std::string &name, ComponentInstantiator instantiator);

		/**
		Creates a component given a name, which will just build it but won't initialize it.
		*/
		IComponent *build(const std::string &entityType) const;
	};

}

#endif