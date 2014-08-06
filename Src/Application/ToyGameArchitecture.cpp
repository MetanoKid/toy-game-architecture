#include "Classic/Application.h"
#include "Evolved/Application.h"

int main(int argc, char **argv) {
	// classic approach
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

	// evolved approach
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

	return 0;
}