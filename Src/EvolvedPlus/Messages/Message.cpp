#include "Message.h"

#include "Pool.h"

namespace EvolvedPlus {

	namespace Messages {

		CMessage::CMessage(const TMessage &type) : _type(type) {

		}

		CMessage::~CMessage() {

		}

		const TMessage &CMessage::getType() const {
			return _type;
		}

		void CMessage::allReferencesReleased() {
			release();
		}

		void CMessage::release() {
			CPool::getInstance().releaseMessage(this);
		}

	}

}