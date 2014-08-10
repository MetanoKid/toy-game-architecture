#ifndef Evolved_Samples_Components_Graphics_H
#define Evolved_Samples_Components_Graphics_H

#include "Evolved/Components/Component.h"

namespace Evolved {

	namespace Samples {

		namespace Components {

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
				bool spawn(const CProperties &data, CLevel *level);

				/**
				Processes a message in which this component is interested.
				*/
				void process(Evolved::Messages::CMessage *message);

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
				virtual void populateWishList(Evolved::Messages::CWishList &wishList) const;
			};

			REGISTER_COMPONENT(CGraphics);
		}

	}

}

#endif