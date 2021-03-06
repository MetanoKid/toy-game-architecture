#include "Application.h"

#include "Components/ComponentFactory.h"
#include "Entity/EntityFactory.h"
#include "Level/LevelFactory.h"
#include "Level/Level.h"

// these next includes exist because of our sample test
#include "Entity/Entity.h"
#include "Samples/Messages/SetPosition.h"

namespace Classic {

#define LEVEL_TO_BUILD "Level.txt"
#define GAME_LOOP_MAX_REPETITIONS 1
#define CONTROLLED_DELTA_TIME 0.16f

	CApplication *CApplication::_instance = NULL;

	CApplication::CApplication() {
		// initialize every subsystem in the architecture
		CComponentFactory::getInstance();
		CEntityFactory::getInstance();
		CLevelFactory::getInstance();
	}

	CApplication::~CApplication() {
		if(_currentLevel) {
			delete _currentLevel;
			_currentLevel = NULL;
		}

		// clean up every subsystem in the architecture
		CEntityFactory::release();
		CLevelFactory::release();
		CComponentFactory::release();
	}

	CApplication::CApplication(const CApplication &factory) {
		_instance = factory._instance;
	}

	CApplication &CApplication::operator=(const CApplication &factory) {
		if(this != &factory) {
			_instance = factory._instance;
		}

		return *this;
	}

	bool CApplication::initialize() {
		// perform application's initialization stuff, like loading a level
		_currentLevel = CLevelFactory::getInstance().build(LEVEL_TO_BUILD);

		return _currentLevel->initialize();
	}

	void CApplication::run() {
		// activate the level, before we can start
		_currentLevel->activate();

		/**
		This game loop should be something similar to:

		while(!exitRequested) {
			_currentLevel->tick(deltaTime);
		}

		Assuming we had no application states to switch to.
		However, for the sake of simplicity and the scope of this architecture,
		we keep it under control and declare how many ticks will be
		performed and the delta time, so our tests are easier to maintain.
		*/

		/*
		int loopCount = 0;

		while(loopCount < GAME_LOOP_MAX_REPETITIONS) {
			// tick our level with a controlled delta time
			_currentLevel->tick(CONTROLLED_DELTA_TIME);

			// clean entities which were scheduled to be deleted
			CEntityFactory::getInstance().deletePendingEntities();

			// next loop
			loopCount++;
		}
		*/

		{
			/**
			Since we need a way to test a sample application, we must have even better control
			of what's happening. So, we'll simulate an execution.
			*/
			CEntity *entity = _currentLevel->getEntityByID(0);

			// first tick (it does nothing)
			_currentLevel->tick(CONTROLLED_DELTA_TIME);
			CEntityFactory::getInstance().deletePendingEntities();

			// send a message
			entity->sendMessage(new Samples::Messages::CSetPosition(Vector3(1.0f, 0.0f, 0.0f)));

			// second tick (message is processed)
			_currentLevel->tick(CONTROLLED_DELTA_TIME);
			CEntityFactory::getInstance().deletePendingEntities();
		}

		// deactivate it, as part of its life cycle
		_currentLevel->deactivate();
	}

	void CApplication::release() {
		if(_instance) {
			delete _instance;
		}

		_instance = NULL;
	}

	CApplication &CApplication::getInstance() {
		if(!_instance) {
			_instance = new CApplication();
		}

		return *_instance;
	}

}