#include "Pool.h"

#include <cassert>
#include <algorithm>

#include "Evolved/Messages/Message.h"
#include "Application/Macros.h"

namespace Evolved {

	namespace Messages {

		CPool *CPool::_instance = NULL;

		CPool::CPool() {

		}

		CPool::~CPool() {
			// destroy every built message
			FOR_IT_CONST(TMessages, itMessageEntry, _messages) {
				FOR_IT_CONST(TMessageList, itReady, itMessageEntry->second.ready) {
					delete *itReady;
				}

				FOR_IT_CONST(TMessageList, itInUse, itMessageEntry->second.inUse) {
					delete *itInUse;
				}
			}

			_messageConstructors.clear();
		}

		CPool::CPool(const CPool &factory) {
			_instance = factory._instance;
		}

		CPool &CPool::operator=(const CPool &factory) {
			if(this != &factory) {
				_instance = factory._instance;
			}

			return *this;
		}

		void CPool::release() {
			if(_instance) {
				delete _instance;
			}

			_instance = NULL;
		}

		CPool &CPool::getInstance() {
			if(!_instance) {
				_instance = new CPool();
			}

			return *_instance;
		}

		void CPool::initialize() {
			FOR_IT_CONST(TMessageConstructors, itConstructor, _messageConstructors) {
				// temporal message used to create the entry
				CMessage *message = itConstructor->second();

				// remember: dinamically knowing type at run time
				const std::type_info *type = &typeid(*message);

				// store which type relates to which name
				_messageNames[type] = itConstructor->first;
				// create an entry
				_messages[&typeid(*message)] = CMessageEntry();
				// get a pointer to the ready instances for easier use
				TMessageList *built = &_messages[&typeid(*message)].ready;

				// not necessary anymore
				delete message;

				// we could use prior message as the first message for the entry, but there might be
				// situations in which we don't want to create any message beforehand
				for(unsigned int i = 0; i < 10; ++i) {
					built->push_back(itConstructor->second());
				}
			}
		}

		void CPool::releaseMessage(CMessage *message) {
			// evaluating type dynamically in run time, instead of statically during compile time
			const std::type_info *type = &typeid(*message);

			// there must be an entry in the pool for this message, or it's an error
			TMessages::iterator itMessages = _messages.find(type);
			assert(itMessages != _messages.end() && "There's no pool entry for a released message.");

			CMessageEntry *entry = &itMessages->second;

			// remove message from the inUse list
			// warning: it's pretty overkill to search for the message every time it's returned,
			// transforming our pool in a possible performance bottleneck
			// try to find a better way of locating it, like unions and linked list as pointed out
			// by http://gameprogrammingpatterns.com/object-pool.html
			// Or, lose track of a message until it's returned again (so, no need to keep an inUse list)
			entry->inUse.erase(std::remove(entry->inUse.begin(),
			                               entry->inUse.end(),
			                               message));
			entry->ready.push_back(message);
		}

		void CPool::add(const std::string &name, MessageInstantiator instantiator) {
			/**
			Each time we include a compilation unit of a component, it will be registered into this factory.
			We'll just override its value since it's cheaper than looking for it and then doing nothing.
			*/
			_messageConstructors[name] = instantiator;
		}

	}

}