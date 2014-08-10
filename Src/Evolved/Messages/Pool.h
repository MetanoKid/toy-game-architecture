#ifndef Evolved_Messages_Pool_H
#define Evolved_Messages_Pool_H

#include <map>
#include <vector>
#include <typeinfo>

namespace Evolved {

	namespace Messages {

		/**
		Forward declarations.
		*/
		class CMessage;

		/**

		*/
		class CPool {

			/**
			The current and unique instance of the singleton.
			*/
			static CPool *_instance;

			/**
			Basic constructor, private as a part of the singleton pattern.
			*/
			CPool();

			/**
			Basic destructor.
			We can only destruct it from inside, so it's private.
			*/
			~CPool();

			/**
			In order to prevent accidental (or intentional) copying of the singleton instance,
			we declare the copy constructor as private so a compile-time error is shown.
			*/
			CPool(const CPool &factory);

			/**
			In order to prevent accidental (or intentional) copying of the singleton instance,
			we declare the assignment operator as private so a compile-time error is shown.
			*/
			CPool &operator=(const CPool &factory);

			/**
			Alias for a function pointer which creates an empty message.
			Those functions will be static functions which exist within the messages.
			*/
			typedef CMessage *(*MessageInstantiator)();

			/**
			Alias for our structure to store message constructors.
			*/
			typedef std::map<std::string, MessageInstantiator> TMessageConstructors;

			/**
			Structure to store message names and functions to create each one of them.
			*/
			TMessageConstructors _messageConstructors;

			/**
			Alias for a list of messages.
			*/
			typedef std::vector<CMessage *> TMessageList;

			/**
			Alias for each entry of our built messages.
			*/
			struct CMessageEntry {
				/**
				List of built messages, awaiting to be used.
				*/
				TMessageList ready;

				/**
				List of messages currently in use.
				*/
				TMessageList inUse;
			};

			/**
			Alias for a map which stores built messages which are ready and being used, by type.
			*/
			typedef std::map<const std::type_info *, CMessageEntry> TMessages;

			/**
			Map which stores built messages, indexed by message type, both ready and in use.
			*/
			TMessages _messages;

			/**
			Initializes the pool with some messages for each type.
			*/
			void initialize();

		public:
			/**
			When the singleton won't be used anymore, we can call this method to destroy the
			current instance. This is the only way of destroying it and not calling it would
			leak it.
			*/
			static void release();

			/**
			Gets the instance of this factory.
			It's a singleton, and by returning instead of a pointer we are subtly declaring
			three characteristics:
			    - It won't be NULL: if it was a pointer, and even if we did our work
				  initializing it, it could be NULL conceptually.
				- It can't be changed: a pointer could be pointed somewhere else.
				- It can't be deleted from outside code: pointers could.
			*/
			static CPool &getInstance();

			template <typename T>
			T *obtainMessage() {
				// get map's key
				const std::type_info *type = &typeid(T);

				// is there any message of that type in the map?
				TMessages::iterator itMessages = _messages.find(type);

				if(itMessages == _messages.end()) {
					return NULL;
				}

				CMessageEntry *entry = &itMessages->second;

				// is there any message ready to be used?
				if(entry->ready.size() == 0) {
					return NULL;
				}

				// extract a message, add it into the inUse list, and return it
				T *message = static_cast<T *>(entry->ready.back());
				entry->ready.pop_back();
				entry->inUse.push_back(message);
				return message;
			}

			/**
			Releases an instance of a message, and returns it to the pool.
			*/
			void releaseMessage(CMessage *message);
		};

	}

}

#endif