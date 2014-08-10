#ifndef Evolved_Messages_MessageTopic_H
#define Evolved_Messages_MessageTopic_H

#include <typeinfo>
#include <map>
#include <vector>

#include "WishList.h"
#include "MessageComparator.h"
#include "Evolved/Entity/EntityID.h"

namespace Evolved {

	/**
	Forward declarations.
	*/
	class IComponent;

	namespace Messages {
		class CMessage;
	}

	namespace Messages {

		/**
		Messaging is managed through a message topic which stores which components are
		interested in which messages.
		Components, if they want to receive certain messages, must suscribe themselves
		to those message types and whenever a message to their entity is sent, they'll
		receive it if types match.
		*/
		class CMessageTopic {
		private:
			/**
			Alias for a list of components.
			Every component in this list will belong to the same entity, conceptually.
			*/
			typedef std::vector<IComponent *> TComponents;

			/**
			Alias for a map of message types to components.
			*/
			typedef std::map<const std::type_info *, TComponents, CMessageComparator> TSuscriptions;

			/**
			Alias for a map of entity ID's to message suscriptions.
			*/
			typedef std::map<TEntityID, TSuscriptions> TEntitySuscriptions;

			/**
			Suscription map, the core of this message topic.
			Every message is sent to a certain entity, so that's why it's first indexed
			by entity's ID. Then, components might be suscribed to a certain kind of
			message (several components might be interested in several messages), so the
			message is only delivered to components which were suscribed.
			*/
			TEntitySuscriptions _suscriptions;

		public:
			/**
			Default constructor.
			*/
			CMessageTopic();

			/**
			Default destructor.
			*/
			~CMessageTopic();

			/**
			Suscribes a component to several message types, as many as declared in the
			WishList.
			*/
			void suscribe(IComponent *component, const CWishList &interestList);

			/**
			Unsuscribes an entity and thus all of its components.
			*/
			void unsuscribe(const TEntityID &entity);

			/**
			Sends a message to any component which was interested in it.
			*/
			bool sendMessage(const TEntityID &destination, CMessage *message, IComponent *emitter) const;
		};

	}

}

#endif