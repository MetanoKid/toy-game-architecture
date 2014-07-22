#include <stdio.h>

#include "Classic/Entity/Entity.h"
#include "Classic/Components/Component.h"
#include "Classic/Messages/Message.h"
#include "Classic/Level/Level.h"

#include "Classic/Entity/EntityFactory.h"
#include "Classic/Level/LevelFactory.h"

#include <vld.h>

int main(int argc, char **argv) {
	// initialize our systems
	Classic::CComponentFactory::getInstance();
	Classic::CEntityFactory::getInstance();
	Classic::CLevelFactory::getInstance();

	// build a level, from file
	Classic::CLevel *level = Classic::CLevelFactory::getInstance().build("Level.txt");

	/*// build a message
	Classic::Messages::CMessage *message = new Classic::Messages::CMessage();

	// send the message to our entity
	entity->sendMessage(message);*/

	// tick our level once
	level->tick(0);

	// delete our level, which should delete the entity as well
	delete level;

	// lastly, release our factories which is the only way of destructing them
	Classic::CEntityFactory::release();
	Classic::CLevelFactory::release();
	Classic::CComponentFactory::release();

	return 0;
}