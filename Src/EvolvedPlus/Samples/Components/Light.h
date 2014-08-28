#ifndef EvolvedPlus_Samples_Components_Light_H
#define EvolvedPlus_Samples_Components_Light_H

#include "EvolvedPlus/Components/Component.h"
#include "Application/Vector3.h"

namespace EvolvedPlus {

	namespace Samples {

		namespace Components {

			/**
			This class represents a light component, which will communicate with the graphics
			engine to tell it where to place a light.
			For the sake of simplicity, it doesn't perform any action since there's
			no actual graphics engine.
			However, it has all of the features every component must use and also those
			which might be used by some of them.
			*/
			class CLight : public IComponent {
				DECLARE_COMPONENT(CLight);

			private:
				/**
				The type of the light to be used.
				*/
				std::string _type;

				/**
				The color for this light.
				*/
				Vector3 _color;

			public:
				/**
				Default constructor, can't have any parameters because of our static
				register into the ComponentFactory.
				*/
				CLight();

				/**
				Default destructor.
				*/
				~CLight();

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

				/**
				This method is just a mock-up to test we can call it from another component,
				given that component has got a reference to this one.
				*/
				const Vector3 &getColor() const;
			};

			REGISTER_COMPONENT(CLight);
		}

	}

}

#endif