#include <stdio.h>

#include "Classic/Entity/Entity.h"
#include "Classic/Components/Component.h"
#include "Classic/Messages/Message.h"
#include "Classic/Level/Level.h"

#include "Classic/Entity/EntityFactory.h"
#include "Classic/Level/LevelFactory.h"

int main(int argc, char **argv) {
	// initialize our systems
	Classic::CComponentFactory::getInstance();
	Classic::CEntityFactory::getInstance();
	Classic::CLevelFactory::getInstance();

	// build a level, from file
	Classic::CLevel *level = Classic::CLevelFactory::getInstance().build("Level.txt");

	// initialize and activate it
	level->initialize();
	level->activate();

	// tick our level once
	level->tick(0);

	// deactivate it, as part of its life cycle
	level->deactivate();

	// delete our level, which should delete the entity as well
	delete level;

	// lastly, release our factories which is the only way of destructing them
	Classic::CEntityFactory::release();
	Classic::CLevelFactory::release();
	Classic::CComponentFactory::release();

	return 0;
}