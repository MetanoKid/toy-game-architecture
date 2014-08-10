#ifndef Evolved_Messages_MessageTypeComparator_H
#define Evolved_Messages_MessageTypeComparator_H

#include <typeinfo>

namespace Evolved {

	namespace Messages {

		/**
		Compares two type_info using their own comparing function.
		*/
		struct CMessageComparator {
			bool operator()(const std::type_info *a, const std::type_info *b) const {
				return a->before(*b);
			}
		};

	}

}


#endif