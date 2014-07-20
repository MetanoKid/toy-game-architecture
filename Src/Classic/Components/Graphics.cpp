#include "Graphics.h"

#include <stdio.h>

namespace Classic {

	namespace Components {

		IMPLEMENT_COMPONENT(CGraphics);

		CGraphics::CGraphics() : IComponent() {
			printf("Building CGraphics!\n");
		}

		CGraphics::~CGraphics() {
			printf("Destroying CGraphics!\n");
		}

	}

}