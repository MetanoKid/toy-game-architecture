#ifndef Evolved_Messages_Message_H
#define Evolved_Messages_Message_H

#include "NotSoSmartPointer.h"
#include "MessageType.h"

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

}

#endif