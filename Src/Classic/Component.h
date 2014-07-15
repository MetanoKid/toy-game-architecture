#ifndef Classic_Component_H
#define Classic_Component_H

#include <string>
#include <vector>

namespace Classic {

	// forward declarations
	class CEntity;
	class CLevelData;
	class CLevel;
	class CMessage;

	/**
	Base class for components in this architecture.
	Components are responsible of processing messages which will allow them to
	interact between them, and are the ones responsible of executing different
	parts of the logic (even if that logic means telling a graphic entity to move).
	*/
	class IComponent {
	private:
		/**
		Alias for our list of messages to be processed.
		*/
		typedef std::vector<CMessage *> TMessages;

		/**
		List of messages left to be processed.
		*/
		TMessages _messages;

	protected:
		/**
		The entity this component is associated to.
		*/
		CEntity *_entity;

		/**
		Tells whether or not a message is accepted by this component.
		Must be overriden by children components if they want to say what they accept.
		*/
		virtual bool accept(CMessage *message) const;

		/**
		Processes a message this component accepts.
		Must be overriden by children components to process those messages.
		*/
		virtual void process(CMessage *message);

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
		virtual bool spawn(const std::string &name, CLevelData *data, CLevel *level);

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
		To be overriden by children components, it's called before doTick finishes.

		@see doTick()
		*/
		virtual void tick(float secs);

		/**
		Gets the entity to which this component is associated.
		*/
		CEntity *getEntity() const;

		/**
		Sets the entity to which this component is associated.
		*/
		void setEntity(CEntity *entity);

		/**
		Tries to add a message to this component's queue of messages.
		*/
		bool enqueueMessage(CMessage *message);
	};

}

#endif