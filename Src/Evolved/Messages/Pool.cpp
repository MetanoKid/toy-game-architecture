#include "Pool.h"

#include <cassert>
#include <algorithm>

#include "Evolved/Samples/Messages/SetPosition.h"
#include "Application/Macros.h"

namespace Evolved {

	namespace Messages {

		CPool *CPool::_instance = NULL;

		CPool::CPool() {
			initialize();
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
			// temporary way of initializing. Future one will be extracting from message constructors
			_messages[&typeid(Samples::Messages::CSetPosition)] = CMessageEntry();
			TMessageList *built = &_messages[&typeid(Samples::Messages::CSetPosition)].ready;

			for(unsigned int i = 0; i < 10; ++i) {
				built->push_back(new Samples::Messages::CSetPosition());
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
			entry->inUse.erase(std::remove(entry->inUse.begin(),
			                               entry->inUse.end(),
			                               message));
			entry->ready.push_back(message);
		}

	}

}