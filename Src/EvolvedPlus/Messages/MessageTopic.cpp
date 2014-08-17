#include "MessageTopic.h"

#include "EvolvedPlus/Messages/Message.h"
#include "EvolvedPlus/Components/Component.h"
#include "Application/Macros.h"

namespace EvolvedPlus {

	namespace Messages {

		CMessageTopic::CMessageTopic() {

		}

		CMessageTopic::~CMessageTopic() {
			_suscriptions.clear();
		}

		void CMessageTopic::suscribe(IComponent *component, const CWishList &interestList) {
			/**
			Using a trick here, read from StackOverflow.
			If you ever want to find a value and create it if it doesn't exist, then use lower_bound
			instead of find. It looks like lower_bound, in case it didn't find the element, returns
			an iterator to the place the element should be inserted, while find would return the
			end of the container if not found.
			That way, we can reuse the result of lower_bound to insert there.

			@see http://stackoverflow.com/a/101980/1257656
			*/
			TEntitySuscriptions::iterator itEntity = _suscriptions.lower_bound(component->getEntity());

			// create it if not existent
			if(itEntity == _suscriptions.end()) {
				// insert where it should be
				itEntity = _suscriptions.insert(itEntity,
				                                TEntitySuscriptions::value_type(component->getEntity(),
				                                                                TSuscriptions()));
			}

			// now start adding suscriptions from the WishList
			FOR_IT_CONST(CWishList::TWishList, itWishList, interestList._interests) {
				TSuscriptions *suscriptions = &itEntity->second;

				// same trick related to find/lower_bound
				TSuscriptions::iterator itSuscription = suscriptions->lower_bound(*itWishList);

				if(itSuscription == suscriptions->end()) {
					// create an entry if it doesn't exist yet
					itSuscription = suscriptions->insert(itSuscription,
					                                     TSuscriptions::value_type(*itWishList,
					                                                               TComponents()));
				}

				// finally, add the component to the suscription list
				itSuscription->second.push_back(component);
			}
		}

		void CMessageTopic::unsuscribe(const TEntityID &entity) {
			TEntitySuscriptions::const_iterator itEntity = _suscriptions.find(entity);

			if(itEntity != _suscriptions.end()) {
				_suscriptions.erase(itEntity);
			}
		}

		bool CMessageTopic::sendMessage(const TEntityID &destination, CMessage *message,
		                                IComponent *emitter) const {
			// due to the nature of the messages in this architecture, we have to check if any
			// component was interested in the message, or else delete it
			bool enqueued = false;

			// first of all, is there any component of the destination entity interested in any message?
			TEntitySuscriptions::const_iterator itEntity = _suscriptions.find(destination);

			if(itEntity != _suscriptions.end()) {
				/**
				If we did typeid(message) we'd get [...]CMessage *, because that's what's known
				at compile time. However, by doing typeid(*message) it checks the type dynamically at
				run time, because it's a dereference of a pointer to a base class.

				@see http://en.wikipedia.org/wiki/Typeid
				*/
				const type_info *type = &typeid(*message);

				// now, is there any component of this entity interested in this message?
				TSuscriptions::const_iterator itSuscription = itEntity->second.find(type);

				if(itSuscription != itEntity->second.end()) {
					// then, start delivering the message to anyone but the emitter
					FOR_IT_CONST(TComponents, itComponent, itSuscription->second) {
						if(*itComponent != emitter) {
							(*itComponent)->enqueueMessage(message);
							enqueued = true;
						}
					}
				}
			}

			// if nobody was interested in it, then we're safe to delete it
			if(!enqueued) {
				message->release();
			}

			return enqueued;
		}

	}

}