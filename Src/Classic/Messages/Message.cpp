#include "Message.h"

namespace Classic {

	namespace Messages {

		CMessage::CMessage(const TMessage &type) : _type(type) {

		}

		CMessage::~CMessage() {

		}

		const TMessage &CMessage::getType() const {
			return _type;
		}

	}

}