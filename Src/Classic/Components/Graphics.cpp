#include "Graphics.h"

#include <stdio.h>

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
				printf("[Graphics] Entity '%s' has a model named '%s'\n",
				       _entity->getName().c_str(), _modelName.c_str());
			} else {
				return false;
			}

			return true;
		}
	}

}