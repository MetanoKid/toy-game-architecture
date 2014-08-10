#ifndef Evolved_Samples_Messages_SetPosition_H
#define Evolved_Samples_Messages_SetPosition_H

#include "Evolved/Messages/Message.h"
#include "Application/Vector3.h"

namespace Evolved {

	namespace Samples {

		namespace Messages {

			/**
			Sample message which has a position. It's used to tell components that an entity
			has moved.
			*/
			class CSetPosition : public Evolved::Messages::CMessage {
			private:
				friend class Evolved::Messages::CPool;

				/**
				New position of the entity.
				*/
				Vector3 _position;

				/**
				Default constructor.
				*/
				CSetPosition();

				/**
				Default destructor.
				*/
				~CSetPosition();

				/**
				Resets the message, ready to be used again.
				*/
				void reset();

			public:
				/**
				Gets the position.
				*/
				const Vector3 &getPosition() const;

				/**
				Initializes the message.
				*/
				CSetPosition *init(const Vector3 &position);
			};

		}

	}

}

#endif