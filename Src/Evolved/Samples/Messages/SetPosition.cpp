#include "SetPosition.h"

namespace Evolved {

	namespace Samples {

		namespace Messages {

			CSetPosition::CSetPosition() : CMessage(Evolved::Messages::SET_POSITION) {

			}

			CSetPosition::~CSetPosition() {

			}

			const Vector3 &CSetPosition::getPosition() const {
				return _position;
			}

			void CSetPosition::reset() {
				_position = Vector3(0.0f, 0.0f, 0.0f);
			}

			CSetPosition *CSetPosition::init(const Vector3 &position) {
				_position = position;

				return this;
			}

		}

	}

}