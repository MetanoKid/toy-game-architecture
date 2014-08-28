#ifndef EvolvedPlus_Samples_Components_Graphics_H
#define EvolvedPlus_Samples_Components_Graphics_H

#include "EvolvedPlus/Components/Component.h"

namespace EvolvedPlus {

	namespace Samples {

		namespace Components {

			/**
			Forward declarations.

			@see CGraphics private member
			*/
			class CLight;

			/**
			This class represents a graphic component, which is the one in charge of
			dealing with the Graphics engine.
			For the sake of simplicity, it doesn't perform any action since there's
			no actual Graphics engine.
			However, it has all of the features every component must use and also those
			which might be used by some of them.
			*/
			class CGraphics : public IComponent {
				DECLARE_COMPONENT(CGraphics);

			private:
				/**
				The name of the model which represents this component.
				Will be passed to the Graphics engine.
				*/
				std::string _modelName;

				/**
				To test we can get a reference to another component, we'll store the
				pointer to a light component in the entity this component is.
				It includes coupling between these classes, but it's just something
				to test out.
				*/
				CLight *_lightComponent;

			public:
				/**
				Default constructor, can't have any parameters because of our static
				register into the ComponentFactory.
				*/
				CGraphics();

				/**
				Default destructor.
				*/
				~CGraphics();

				/**
				Called as the second part of the two-step initialization.
				*/
				bool spawn(const CEntityProperties &data, CLevel *level);

				/**
				Processes a message in which this component is interested.
				*/
				void process(EvolvedPlus::Messages::CMessage *message);

				/**
				Activate this component.
				*/
				bool activate();

				/**
				Deactivate this component.
				*/
				void deactivate();

				/**
				Perform per-frame behavior.
				*/
				void tick(float secs);

				/**
				Populates a message WishList in which this component is interested in.
				Must be overriden by child components if they want to say what they accept.
				*/
				virtual void populateWishList(EvolvedPlus::Messages::CWishList &wishList) const;
			};

			REGISTER_COMPONENT(CGraphics);
		}

	}

}

#endif