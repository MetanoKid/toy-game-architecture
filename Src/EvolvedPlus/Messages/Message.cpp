#include "Message.h"

#include "Pool.h"

namespace EvolvedPlus {

	namespace Messages {

		CMessage::CMessage() {

		}

		CMessage::~CMessage() {

		}

		void CMessage::allReferencesReleased() {
			release();
		}

		void CMessage::release() {
			CPool::getInstance().releaseMessage(this);
		}

	}

}