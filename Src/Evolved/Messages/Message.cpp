#include "Message.h"

namespace Evolved {

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