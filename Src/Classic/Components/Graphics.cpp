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
	}

}