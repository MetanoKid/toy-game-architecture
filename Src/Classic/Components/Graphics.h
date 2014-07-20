#ifndef Classic_Components_Graphics_H
#define Classic_Components_Graphics_H

#include "Component.h"

namespace Classic {

	//namespace Components {

	class CGraphics : public IComponent {
		DECLARE_COMPONENT(CGraphics);
		/*public:
			static IComponent *create();
			static bool registerComponent();*/

	public:
		CGraphics();
		~CGraphics();
	};

	REGISTER_COMPONENT(CGraphics);
	//static bool RegisteredInFactory_CGraphics = CGraphics::registerComponent();
	//}

}

#endif