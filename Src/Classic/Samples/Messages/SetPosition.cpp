#include "SetPosition.h"

namespace Classic {

	namespace Samples {

		namespace Messages {

			CSetPosition::CSetPosition(const Vector3 &position) : CMessage(Classic::Messages::SET_POSITION),
				_position(position) {

			}

			CSetPosition::~CSetPosition() {

			}

			const Vector3 &CSetPosition::getPosition() const {
				return _position;
			}

		}

	}

}