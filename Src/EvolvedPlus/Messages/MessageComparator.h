#ifndef EvolvedPlus_Messages_MessageTypeComparator_H
#define EvolvedPlus_Messages_MessageTypeComparator_H

#include <typeinfo>

namespace EvolvedPlus {

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