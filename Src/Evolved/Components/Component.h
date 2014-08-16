#ifndef Evolved_Component_H
#define Evolved_Component_H

#include <string>
#include <vector>

#include "ComponentFactory.h"
#include "Evolved/Entity/EntityID.h"
#include "Evolved/Entity/EntityProperties.h"
#include "Evolved/Messages/WishList.h"

namespace Evolved {

	/**
	Forward declarations.
	*/
	class CLevel;

	namespace Messages {
		class CMessage;
	}

	/**
	Base class for components in this architecture.
	Components are responsible of processing messages which will allow them to
	interact between them, and are the ones responsible of executing different
	parts of the logic (even if that logic means telling a graphic entity to move).

	Child components must provide some macros to add them to the component factory,
	so they are available when instantiating entities.
	*/
	class IComponent {
	private:
		/**
		Alias for our list of messages to be processed.
		*/
		typedef std::vector<Messages::CMessage *> TMessages;

		/**
		List of messages left to be processed.
		*/
		TMessages _messages;

	protected:
		/**
		The entity this component is associated to.
		*/
		TEntityID _entity;

		/**
		Processes a message this component accepts.
		Must be overriden by child components to process those messages.
		*/
		virtual void process(Messages::CMessage *message);

	public:
		/**
		Base constructor, takes the entity to which the component is associated.
		Represents the first part of component's instantiation.
		*/
		IComponent();

		/**
		Base destructor, virtual as this is expected to be inherited.
		*/
		virtual ~IComponent();

		/**
		Initializes component's basic data, as the second part of  the component's
		initialization.
		*/
		virtual bool spawn(const CEntityProperties &data, CLevel *level);

		/**
		Activates the component.
		*/
		virtual bool activate();

		/**
		Deactivates the component.
		*/
		virtual void deactivate();

		/**
		Called once per frame, this method will process queued messages and
		delegate to tick.
		*/
		void doTick(float secs);

		/**
		To be overriden by child components, it's called before doTick finishes.

		@see doTick()
		*/
		virtual void tick(float secs);

		/**
		Gets the entity to which this component is associated.
		*/
		const TEntityID &getEntity() const;

		/**
		Sets the entity to which this component is associated.
		*/
		void setEntity(const TEntityID &entity);

		/**
		Adds a message to this component's queue of messages.
		*/
		void enqueueMessage(Messages::CMessage *message);

		/**
		Populates a message WishList in which this component is interested in.
		Must be overriden by child components if they want to say what they accept.
		*/
		virtual void populateWishList(Messages::CWishList &wishList) const;

		/**
		Gets the name of the component, which is the "stringification" of the class name.
		It's used when the architecture spawns a component, so it can just access data
		addressed to it, and not other components.
		It's automatically implemented using mandatory-use component macros.
		*/
		virtual std::string getName() const = 0;
	};

	/**
	Child components must use these next macros to register themselves into the
	component factory at start up, since we need them when instantiating entities.
	*/

	/**
	This macro declares some static methods that are part of every child component
	class that will be defined.
	Must be used within the component class' declaration, preferable as the first entry.
	The only parameter of the macro isn't used, but exists to provide an uniform structure.
	*/
#define DECLARE_COMPONENT(ComponentClass) \
public: \
	/** \
	Creates an instance of the component in which this is defined. \
	*/ \
	static IComponent *create(); \
	\
	/** \
	Registers the component into the component factory. \
	*/ \
	static bool registerComponent(); \
	\
	/**
	Defines mandatory method. \
	*/ \
	std::string getName() const;

	/**
	This macro defines some static methods that are part of every component, declared by
	macro DECLARE_COMPONENT.
	Must be used when providing the implementation of a component.
	*/
#define IMPLEMENT_COMPONENT(ComponentClass) \
	IComponent *ComponentClass::create() { \
		return new ComponentClass(); \
	} \
	\
	bool ComponentClass::registerComponent() { \
		CComponentFactory::getInstance().add(#ComponentClass, ComponentClass::create); \
		/* just return true always because we need to return something for REGISTER_COMPONENT macro to work correctly */ \
		return true; \
	} \
	\
	std::string ComponentClass::getName() const { \
		return #ComponentClass; \
	}

	/**
	This macro registers the function to create an instance of the component into the
	component factory.
	Since we can't call a function unless it's part of a static variable, we create one for each
	component that is registered. That variable will only be available within the component's file.
	There will be one of these variables each time we include the compilation unit of a component.

	@see CComponentFactory::add()
	*/
#define REGISTER_COMPONENT(ComponentClass) \
	static bool RegisteredInFactory_##ComponentClass = ComponentClass::registerComponent();

}

#endif