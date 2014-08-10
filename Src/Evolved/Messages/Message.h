#ifndef Evolved_Messages_Message_H
#define Evolved_Messages_Message_H

#include "NotSoSmartPointer.h"
#include "MessageType.h"
#include "Pool.h"

namespace Evolved {

	namespace Messages {

		/**
		Messages are the only way of communicating entities between them. Entities
		send messages and their components process them to perform their behaviors.
		*/
		class CMessage : public NotSoSmartPointer {
		protected:
			/**
			Type of this message.
			*/
			TMessage _type;

			/**
			Only a Message Pool can create and destroy messages, so constructor and
			destructor are only available for it and children messages.
			*/
			friend class CPool;

			/**
			Default constructor, sets the type of the message.
			*/
			CMessage(const TMessage &type = TMessage::UNASSIGNED);

			/**
			Default destructor.
			*/
			virtual ~CMessage();

			/**
			Whenever a message is returned to a Message Pool, it must be reset so it
			can be reused later on.
			Children messages must implement this method.
			*/
			virtual void reset() = 0;

			/**
			Whenever every reference to this message is released, we will return it to
			the object pool.
			*/
			void allReferencesReleased();

		public:
			/**
			Gets the type of this message.
			*/
			const TMessage &getType() const;

			/**
			Returns this instance to the Message Pool.
			*/
			void release();
		};

	}

	/**
	Child messages must use these next macros to register themselves into the
	message pool at start up.
	*/

	/**
	This macro declares some static methods that are part of every child message
	class that will be defined.
	Must be used within the message class' declaration, preferable as the first entry.
	The only parameter of the macro isn't used, but exists to provide an uniform structure.
	*/
#define DECLARE_MESSAGE(MessageClass) \
public: \
	/** \
	Creates an instance of the message in which this is defined. \
	*/ \
	static Evolved::Messages::CMessage *create(); \
	\
	/** \
	Registers the message into the message pool. \
	*/ \
	static bool registerMessage();

	/**
	This macro defines some static methods that are part of every message, declared by
	macro DECLARE_MESSAGE.
	Must be used when providing the implementation of a message.
	*/
#define IMPLEMENT_MESSAGE(MessageClass) \
	Evolved::Messages::CMessage *MessageClass::create() { \
		return new MessageClass(); \
	} \
	\
	bool MessageClass::registerMessage() { \
		Evolved::Messages::CPool::getInstance().add(#MessageClass, MessageClass::create); \
		/* just return true always because we need to return something for REGISTER_MESSAGE macro to work correctly */ \
		return true; \
	}

	/**
	This macro registers the function to create an instance of the message into the
	message pool.
	Since we can't call a function unless it's part of a static variable, we create one for each
	message that is registered. That variable will only be available within the message's file.
	There will be one of these variables each time we include the compilation unit of a message.

	@see CPool::add()
	*/
#define REGISTER_MESSAGE(MessageClass) \
	static bool RegisteredInPool_##MessageClass = MessageClass::registerMessage();
}

#endif