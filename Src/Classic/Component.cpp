#include "Component.h"
#include "Messages/Message.h"
#include "Application/Macros.h"

namespace Classic {

	IComponent::IComponent() : _entity(NULL) {

	}

	IComponent::~IComponent() {
		// destroy messages which weren't processed
		FOR_IT_CONST(TMessages, it, _messages) {
			delete(*it);
		}

		_messages.clear();
	}

	bool IComponent::spawn(const std::string &name, CLevelData *data, CLevel *level) {
		// to be overriden by children classes
		return true;
	}

	bool IComponent::activate() {
		// to be overriden by children classes
		return true;
	}

	void IComponent::deactivate() {
		// to be overriden by children classes
	}

	void IComponent::doTick(float secs) {
		// process messages
		FOR_IT_CONST(TMessages, it, _messages) {
			// process the message and release a reference from it
			process(*it);
			(*it)->releaseReference();
		}

		// now empty out message list, since we've processed them
		_messages.clear();

		// now that messages are processed, let user execute some behavior
		tick(secs);
	}

	void IComponent::tick(float secs) {
		// to be overriden by children components
	}

	CEntity *IComponent::getEntity() const {
		return _entity;
	}

	void IComponent::setEntity(CEntity *entity) {
		_entity = entity;
	}

	bool IComponent::accept(Messages::CMessage *message) const {
		// to be overriden by children components
		return false;
	}

	void IComponent::process(Messages::CMessage *message) {
		// to be overriden by children components
	}

	bool IComponent::enqueueMessage(Messages::CMessage *message) {
		bool accepted = accept(message);

		if(accepted) {
			// add a reference and add enqueue the message
			message->addReference();
			_messages.push_back(message);
		}

		return accepted;
	}

}