#include "SetPosition.h"

namespace EvolvedPlus {

	namespace Samples {

		namespace Messages {

			IMPLEMENT_MESSAGE(CSetPosition);

			CSetPosition::CSetPosition() : CMessage(EvolvedPlus::Messages::SET_POSITION) {

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