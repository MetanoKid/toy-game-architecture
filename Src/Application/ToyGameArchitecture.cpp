#include "Classic/Application.h"
#include "Evolved/Application.h"
#include "EvolvedPlus/Application.h"

/**
Entry point of this architecture, to show its behavior and flow during the executions.
Every approach is presented here and a simple execution is provided. There are no console
messages to know what's happening unless you add them, but you can turn on the debugger
at any point and start checking its flow.

It's been proven free of memory leaks with Visual Leak Detector but be careful if you
comment out an approach totally: by the way components are registered into their factories,
we need to release those factories so everything is cleared. That's why every
application.release() is important and can't be removed, or else leaks will appear.
@see Component.h, Message.h to get more info on this restriction.
*/
int main(int argc, char **argv) {
	// Classic approach
	{
		// build the application
		Classic::CApplication &application = Classic::CApplication::getInstance();

		// initialize it and run if initialization was successful
		if(application.initialize()) {
			application.run();
		}

		// finally, destroy the application
		application.release();
	}

	// Evolved approach
	{
		// build the application
		Evolved::CApplication &application = Evolved::CApplication::getInstance();

		// initialize it and run if initialization was successful
		if(application.initialize()) {
			application.run();
		}

		// finally, destroy the application
		application.release();
	}

	// EvolvedPlus approach
	{
		// build the application
		EvolvedPlus::CApplication &application = EvolvedPlus::CApplication::getInstance();

		// initialize it and run if initialization was successful
		if(application.initialize()) {
			application.run();
		}

		// finally, destroy the application
		application.release();
	}

	return 0;
}