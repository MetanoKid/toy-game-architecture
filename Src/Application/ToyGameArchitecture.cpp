#include <stdio.h>

#include "Classic/Entity/Entity.h"
#include "Classic/Components/Component.h"
#include "Classic/Messages/Message.h"
#include "Classic/Level/Level.h"

#include "Classic/Entity/EntityFactory.h"
#include "Classic/Level/LevelFactory.h"

int main(int argc, char **argv) {
	Classic::CLevelFactory::getInstance().build("Level.txt");

	// build the entity factory
	Classic::CEntityFactory &entityFactory = Classic::CEntityFactory::getInstance();

	// build an entity
	Classic::CEntity *entity = entityFactory.build("EntityTest");

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

	// lastly, release the entity factory which is the only way of destructing it
	Classic::CEntityFactory::release();

	return 0;
}