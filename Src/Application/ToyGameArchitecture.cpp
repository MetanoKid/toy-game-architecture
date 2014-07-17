#include <stdio.h>

#include "Classic/Entity/Entity.h"
#include "Classic/Components/Component.h"
#include "Classic/Messages/Message.h"
#include "Classic/Level/Level.h"

int main(int argc, char **argv) {
	// build an entity
	Classic::TEntityID id = 0;
	Classic::CEntity *entity = new Classic::CEntity(id);
	Classic::IComponent *component = new Classic::IComponent();
	entity->addComponent(component);

	// build a level
	Classic::CLevel *level = new Classic::CLevel();
	level->addEntity(entity);

	// build a message
	Classic::Messages::CMessage *message = new Classic::Messages::CMessage();

	// send the message to our entity
	entity->sendMessage(message);

	// tick our level once
	level->tick(0);

	// delete our level, which should delete the entity as well
	delete level;

	return 0;
}