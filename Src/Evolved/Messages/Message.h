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
		private:
			/**
			Type of this message.
			*/
			TMessage _type;

		public:
			/**
			Default constructor, sets the type of the message.
			*/
			CMessage(const TMessage &type = TMessage::UNASSIGNED);

			/**
			Default destructor.
			*/
			virtual ~CMessage();

			/**
			Gets the type of this message.
			*/
			const TMessage &getType() const;
		};

	}

}

#endif