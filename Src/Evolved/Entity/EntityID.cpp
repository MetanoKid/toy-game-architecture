#include "EntityID.h"

#include <cassert>

namespace Evolved {

	TEntityID CEntityID::_nextID = CEntityID::FIRST_ID;

	TEntityID CEntityID::nextID() {
		TEntityID id = CEntityID::_nextID;

		assert(id != CEntityID::LAST_ID && "No more entity IDs available");

		_nextID++;
		return id;
	}

}