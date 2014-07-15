#include <stdio.h>

#include "Classic/Entity.h"
#include "Classic/Component.h"
#include "Classic/Messages/Message.h"

int main(int argc, char **argv) {
	Classic::TEntityID id = 0;
	Classic::CEntity *entity = new Classic::CEntity(id);
	Classic::IComponent *component = new Classic::IComponent();
	Classic::Messages::CMessage *message = new Classic::Messages::CMessage();

	entity->addComponent(component);
	entity->sendMessage(message);
	entity->tick(0);

	delete entity;

	return 0;
}