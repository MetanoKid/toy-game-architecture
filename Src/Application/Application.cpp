#include "Application.h"

#include "Classic/Components/ComponentFactory.h"
#include "Classic/Entity/EntityFactory.h"
#include "Classic/Level/LevelFactory.h"

#include "Classic/Level/Level.h"

namespace Application {

#define GAME_LOOP_MAX_REPETITIONS 1
#define CONTROLLED_DELTA_TIME 0.16f

	CApplication *CApplication::_instance = NULL;

	CApplication::CApplication() {
		// initialize every subsystem in the architecture
		Classic::CComponentFactory::getInstance();
		Classic::CEntityFactory::getInstance();
		Classic::CLevelFactory::getInstance();
	}

	CApplication::~CApplication() {
		if(_currentLevel) {
			delete _currentLevel;
			_currentLevel = NULL;
		}

		// clean up every subsystem in the architecture
		Classic::CEntityFactory::release();
		Classic::CLevelFactory::release();
		Classic::CComponentFactory::release();
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
		_currentLevel = Classic::CLevelFactory::getInstance().build("Level.txt");

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
		int loopCount = 0;

		while(loopCount < GAME_LOOP_MAX_REPETITIONS) {
			// tick our level with a controlled delta time
			_currentLevel->tick(CONTROLLED_DELTA_TIME);

			// clean entities which were scheduled to be deleted
			Classic::CEntityFactory::getInstance().deletePendingEntities();

			// next loop
			loopCount++;
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