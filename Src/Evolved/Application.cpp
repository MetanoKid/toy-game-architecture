#include "Application.h"

#include "Components/ComponentFactory.h"
#include "Entity/EntityFactory.h"
#include "Level/LevelFactory.h"
#include "Level/Level.h"
#include "Messages/Pool.h"
#include "Config/Config.h"

// these next includes exist because of our sample test
#include "Samples/Messages/SetPosition.h"

namespace Evolved {

	CApplication *CApplication::_instance = NULL;

	CApplication::CApplication() {
		// initialize every subsystem in the architecture
		Messages::CPool::getInstance().initialize();
		CComponentFactory::getInstance();
		CEntityFactory::getInstance();
		CLevelFactory::getInstance();
		CConfig::getInstance();
	}

	CApplication::~CApplication() {
		if(_currentLevel) {
			delete _currentLevel;
			_currentLevel = NULL;
		}

		// clean up every subsystem in the architecture
		CConfig::release();
		CEntityFactory::release();
		CLevelFactory::release();
		CComponentFactory::release();
		Messages::CPool::release();
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
		std::string fileName;

		if(!CConfig::getInstance().get<std::string>("level_evolved", fileName)) {
			assert(false && "Couldn't find property level in the config file.");
		}

		_currentLevel = CLevelFactory::getInstance().build(fileName);

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

			// next loop
			loopCount++;
		}
		*/

		{
			// extract the controlled delta time from the config file
			float deltaTime;

			if(!CConfig::getInstance().get<float>("controlled_delta_time", deltaTime)) {
				deltaTime = 0.16f;
			}

			/**
			Since we need a way to test a sample application, we must have even better control
			of what's happening. So, we'll simulate an execution.
			*/
			TEntityID entity = CEntityID::FIRST_ID;

			// first tick (it does nothing)
			_currentLevel->tick(deltaTime);

			// send a message
			Messages::CPool &pool = Messages::CPool::getInstance();
			Samples::Messages::CSetPosition *message = pool.obtainMessage<Samples::Messages::CSetPosition>();
			message->init(Vector3(1.0f, 0.0f, 0.0f));
			_currentLevel->sendMessage(entity, message);

			// second tick (message is processed)
			_currentLevel->tick(deltaTime);
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