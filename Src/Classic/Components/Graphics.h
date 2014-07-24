#ifndef Classic_Components_Graphics_H
#define Classic_Components_Graphics_H

#include "Component.h"

namespace Classic {

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
			bool spawn(const CLevelData &data, CLevel *level);

			/**
			Tells whether or not this component is interested in a message.
			*/
			bool accept(Messages::CMessage *message) const;

			/**
			Processes a message in which this component is interested.
			*/
			void process(Messages::CMessage *message);

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

		REGISTER_COMPONENT(CGraphics);
	}

}

#endif