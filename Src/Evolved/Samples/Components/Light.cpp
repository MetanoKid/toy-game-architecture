#include "Light.h"

#include "Evolved/Samples/Messages/SetPosition.h"

namespace Evolved {

	namespace Samples {

		namespace Components {

			IMPLEMENT_COMPONENT(CLight);

			CLight::CLight() : IComponent(), _type("") {

			}

			CLight::~CLight() {

			}

			bool CLight::spawn(const CEntityProperties &data, CLevel *level) {
				// try to get some data, which we take as mandatory
				if(data.get<std::string>(this, "type", _type) &&
				   data.get<Vector3>(this, "color", _color)) {
					// got a light, so now tell the Graphics engine to create one
					return true;
				}

				return false;
			}

			void CLight::populateWishList(Evolved::Messages::CWishList &wishList) const {
				// we're interested in these messages:
				wishList.add<Messages::CSetPosition>();
			}

			void CLight::process(Evolved::Messages::CMessage *message) {
				switch(message->getType()) {
					case Evolved::Messages::SET_POSITION: {
							Messages::CSetPosition *m = static_cast<Messages::CSetPosition *>(message);

							// use m->getPosition() to tell the Graphics engine to move the light
						}
						break;
				}
			}

			bool CLight::activate() {
				// perform operations when activating, if any
				// example: add the light to a graphic scene
				return true;
			}

			void CLight::deactivate() {
				// perform operations when deactivating, if any
				// example: remove the light from a graphic scene
			}

			void CLight::tick(float secs) {
				// tell the Graphics engine any per-tick information that may be needed
			}

		}

	}

}