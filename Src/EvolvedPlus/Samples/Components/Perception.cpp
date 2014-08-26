#include "Perception.h"

#include "EvolvedPlus/Entity/EntityID.h"

namespace EvolvedPlus {

	namespace Samples {

		namespace Components {

			IMPLEMENT_COMPONENT(CPerception);

			CPerception::CPerception() : IComponent(), _type("") {

			}

			CPerception::~CPerception() {

			}

			bool CPerception::spawn(const CEntityProperties &data, CLevel *level) {
				// try to get some data, which we take as mandatory
				if(data.get<std::string>(this, "type", _type)) {
					// got a perception type, so now tell the AI engine to create one for us
					return true;
				}

				return false;
			}

			bool CPerception::activate() {
				// perform operations when activating, if any
				// example: register the perception entity in the AI engine
				return true;
			}

			void CPerception::deactivate() {
				// perform operations when deactivating, if any
				// example: unregister the perception entity in the AI engine
			}

			void CPerception::tick(float secs) {
				// tell the AI engine any per-tick information that may be needed
			}

		}

	}

}