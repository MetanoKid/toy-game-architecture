#ifndef Evolved_Messages_WishList_H
#define Evolved_Messages_WishList_H

#include <vector>
#include <typeinfo>

namespace Evolved {

	namespace Messages {

		/**
		Components must declare which messages they're interested in.
		In the suscription stage of their life cycle, they will be passed
		an empty CWishList that they must fill with any message they want
		to receive. Later on, that CWishList will be processed and suscriptions
		will be created.
		*/
		class CWishList {
		private:
			/**
			Only a message topic should know how to iterate over a
			WishList to create suscriptions, so make it friend class.
			*/
			friend class CMessageTopic;

			/**
			Alias for a list of message types.
			*/
			typedef std::vector<const std::type_info *> TWishList;

			/**
			List of message types a component is interested in.
			*/
			TWishList _interests;

		public:
			/**
			Default constructor.
			*/
			CWishList() {

			}

			/**
			Default destructor.
			*/
			~CWishList() {
				_interests.clear();
			}

			/**
			Used by components, this method is used to declare which messages
			they are interested in, by type. It's also chainable, so one could
			do:

			wishList.add<TypeA>().add<TypeB>().add<TypeC>();
			*/
			template <typename T>
			CWishList &add() {
				_interests.push_back(&typeid(T));

				return *this;
			}

			/**
			Clears the messages in this WishList so it's reusable again.
			*/
			void clear() {
				_interests.clear();
			}
		};

	}

}

#endif