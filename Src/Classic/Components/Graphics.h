#ifndef Classic_Components_Graphics_H
#define Classic_Components_Graphics_H

#include "Component.h"

namespace Classic {

	namespace Components {

		class CGraphics : public IComponent {
			DECLARE_COMPONENT(CGraphics);

		private:
			std::string _modelName;

		public:
			CGraphics();
			~CGraphics();

			bool spawn(const CLevelData &data, CLevel *level);
		};

		REGISTER_COMPONENT(CGraphics);
	}

}

#endif