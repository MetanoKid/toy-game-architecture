#include "Entity.h"

namespace Classic {

	CEntity::CEntity() {

	}

	CEntity::~CEntity() {

	}

	void CEntity::sayHi(const std::string &name) const {
		printf("Hello, %s\n", name.c_str());
	}

}