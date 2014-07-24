#include "Graphics.h"

#include "Classic/Entity/Entity.h"

namespace Classic {

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

			return true;
		}

		bool CGraphics::accept(Messages::CMessage *message) const {
			// not interested in any message
			return false;
		}

		void CGraphics::process(Messages::CMessage *message) {
			// since it's not interested in any message, no processing must be done
		}

		bool CGraphics::activate() {
			// perform operations when activating, if any
			return true;
		}

		void CGraphics::deactivate() {
			// perform operations when deactivating, if any
		}

		void CGraphics::tick(float secs) {
			// tell the Graphics engine where this graphic entity is right now
		}
	}

}