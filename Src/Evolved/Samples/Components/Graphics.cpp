#include "Graphics.h"

#include "Evolved/Samples/Messages/SetPosition.h"

namespace Evolved {

	namespace Samples {

		namespace Components {

			IMPLEMENT_COMPONENT(CGraphics);

			CGraphics::CGraphics() : IComponent(), _modelName("") {

			}

			CGraphics::~CGraphics() {

			}

			bool CGraphics::spawn(const CLevelData &data, CLevel *level) {
				// try to get some data, which we take as mandatory
				if(data.get<std::string>("model", _modelName)) {
					// got a model name, so now tell the graphics engine to load it
				} else {
					return false;
				}

				// perform extra operations like creating a graphic entity, and keeping a reference

				return true;
			}

			void CGraphics::populateWishList(Evolved::Messages::CWishList &wishList) const {
				// we're interested in these messages:
				wishList.add<Messages::CSetPosition>();
			}

			void CGraphics::process(Evolved::Messages::CMessage *message) {
				switch(message->getType()) {
					case Evolved::Messages::SET_POSITION: {
							Messages::CSetPosition *m = static_cast<Messages::CSetPosition *>(message);

							// use m->getPosition() to tell the Graphics engine to move the entity
						}
						break;
				}
			}

			bool CGraphics::activate() {
				// perform operations when activating, if any
				// example: add the graphic entity to a graphic scene
				return true;
			}

			void CGraphics::deactivate() {
				// perform operations when deactivating, if any
				// example, remove the graphic entity from a graphic scene
			}

			void CGraphics::tick(float secs) {
				// tell the Graphics engine any per-tick information that may be needed
			}

		}

	}

}