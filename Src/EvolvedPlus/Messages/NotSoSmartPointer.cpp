#include "NotSoSmartPointer.h"

namespace EvolvedPlus {

	namespace Messages {

		NotSoSmartPointer::NotSoSmartPointer() : _referenceCount(0) {

		}

		NotSoSmartPointer::~NotSoSmartPointer() {

		}

		void NotSoSmartPointer::addReference() {
			++_referenceCount;
		}

		void NotSoSmartPointer::releaseReference() {
			--_referenceCount;

			if(_referenceCount == 0) {
				allReferencesReleased();
			}
		}

	}

}