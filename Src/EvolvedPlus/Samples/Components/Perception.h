#ifndef EvolvedPlus_Samples_Components_Perception_H
#define EvolvedPlus_Samples_Components_Perception_H

#include "EvolvedPlus/Components/Component.h"
#include "Application/Vector3.h"

namespace EvolvedPlus {

	namespace Samples {

		namespace Components {

			/**
			This class represents a perception component, which will communicate with the
			AI engine to tell it which kind of perception this entity has.
			For the sake of simplicity, it doesn't perform any action since there's
			no actual AI engine.
			However, it has all of the features every component must use and also those
			which might be used by some of them.
			*/
			class CPerception : public IComponent {
				DECLARE_COMPONENT(CPerception);

			private:
				/**
				The perception type to be used.
				*/
				std::string _type;

			public:
				/**
				Default constructor, can't have any parameters because of our static
				register into the ComponentFactory.
				*/
				CPerception();

				/**
				Default destructor.
				*/
				~CPerception();

				/**
				Called as the second part of the two-step initialization.
				*/
				bool spawn(const CEntityProperties &data, CLevel *level);

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
			};

			REGISTER_COMPONENT(CPerception);
		}

	}

}

#endif