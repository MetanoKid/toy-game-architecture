#ifndef Classic_Samples_Messages_SetPosition_H
#define Classic_Samples_Messages_SetPosition_H

#include "Classic/Messages/Message.h"
#include "Application/Vector3.h"

namespace Classic {

	namespace Samples {

		namespace Messages {

			/**
			Sample message which has a position. It's used to tell components that an entity
			has moved.
			*/
			class CSetPosition : public Classic::Messages::CMessage {
			private:
				/**
				New position of the entity.
				*/
				Vector3 _position;

			public:
				/**
				Basic constructor, the only way of setting message's position.
				*/
				CSetPosition(const Vector3 &position);

				/**
				Default destructor.
				*/
				~CSetPosition();

				/**
				Gets the position.
				*/
				const Vector3 &getPosition() const;
			};

		}

	}

}

#endif