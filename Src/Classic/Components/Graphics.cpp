#include "Graphics.h"

#include <stdio.h>

namespace Classic {

	//namespace Components {

	IMPLEMENT_COMPONENT(CGraphics);

	CGraphics::CGraphics() : IComponent() {
		printf("Building CGraphics!\n");
	}

	CGraphics::~CGraphics() {
		printf("Destroying CGraphics!\n");
	}

	/*IComponent *CGraphics::create() {
		return new CGraphics();
	}

	bool CGraphics::registerComponent() {
		CComponentFactory::getInstance().add("CGraphics", CGraphics::create);
		// just return true always because we need to return something for REGISTER_COMPONENT macro to work correctly
		return true;
	}*/

	//}

}