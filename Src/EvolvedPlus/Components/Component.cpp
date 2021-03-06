#include "Component.h"
#include "EvolvedPlus/Entity/EntityProperties.h"
#include "EvolvedPlus/Messages/Message.h"
#include "Application/Macros.h"

namespace EvolvedPlus {

	IComponent::IComponent(unsigned int priority, float updateFrequency) :
		_entity(CEntityID::UNASSIGNED), _priority(priority), _updateFrequency(updateFrequency),
		_currentUploadFrequency(0.0f) {

	}

	IComponent::~IComponent() {
		// destroy messages which weren't processed
		FOR_IT_CONST(TMessages, it, _messages) {
			(*it)->release();
		}

		_messages.clear();
	}

	bool IComponent::spawn(const CEntityProperties &data, CLevel *level) {
		// to be overriden by child classes
		return true;
	}

	bool IComponent::activate() {
		// to be overriden by child classes
		return true;
	}

	void IComponent::deactivate() {
		// to be overriden by child classes
	}

	void IComponent::doTick(float secs) {
		// based on our update frequency, do we have to tick yet?
		if(_updateFrequency == 0.0f) {
			processMessages();
			tick(secs);
		} else if(_updateFrequency > 0.0f) {
			_currentUploadFrequency += secs;

			if(_currentUploadFrequency >= _updateFrequency) {
				processMessages();

				while(_currentUploadFrequency >= _updateFrequency) {
					tick(_updateFrequency);
					_currentUploadFrequency -= _updateFrequency;
				}
			}
		}
	}

	void IComponent::processMessages() {
		FOR_IT_CONST(TMessages, it, _messages) {
			// process the message and release a reference from it
			process(*it);
			(*it)->releaseReference();
		}

		// now empty out message list, since we've processed them
		_messages.clear();
	}

	void IComponent::tick(float secs) {
		// to be overriden by child components
	}

	const TEntityID &IComponent::getEntity() const {
		return _entity;
	}

	void IComponent::setEntity(const TEntityID &entity) {
		_entity = entity;
	}

	void IComponent::populateWishList(Messages::CWishList &wishList) const {
		// to be overriden by child components
	}

	void IComponent::process(Messages::CMessage *message) {
		// to be overriden by child components
	}

	void IComponent::enqueueMessage(Messages::CMessage *message) {
		// add a reference and enqueue the message
		message->addReference();
		_messages.push_back(message);
	}

	unsigned int IComponent::getPriority() const {
		return _priority;
	}
}