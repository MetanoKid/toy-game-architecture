#include <stdio.h>

#include "Classic/Entity.h"

int main(int argc, char **argv) {
	Classic::CEntity *entity = new Classic::CEntity();
	entity->sayHi("World");
	delete entity;

	return 0;
}