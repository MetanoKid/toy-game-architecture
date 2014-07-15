#include <stdio.h>

#include "Classic/Entity.h"
#include "Classic/Component.h";

int main(int argc, char **argv) {
	Classic::TEntityID id = 0;
	Classic::CEntity *entity = new Classic::CEntity(id);
	Classic::IComponent *component = new Classic::IComponent();

	entity->addComponent(component);
	entity->tick(0);

	delete entity;

	return 0;
}