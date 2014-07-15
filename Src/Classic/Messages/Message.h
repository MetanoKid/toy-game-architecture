#ifndef Classic_Messages_Message_H
#define Classic_Messages_Message_H

#include "NotSoSmartPointer.h"
#include "MessageType.h"

namespace Classic {

	namespace Messages {

		class CMessage : public NotSoSmartPointer {
		private:
			TMessage _type;

		public:
			CMessage(const TMessage &type = TMessage::UNASSIGNED);

			virtual ~CMessage();

			const TMessage &getType() const;
		};

	}

}

#endif