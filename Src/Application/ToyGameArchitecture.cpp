#include "Application.h"

int main(int argc, char **argv) {
	// build the application
	Application::CApplication &application = Application::CApplication::getInstance();

	// initialize it and run if initialization was successful
	if(application.initialize()) {
		application.run();
	}

	// finally, destroy the application
	application.release();

	return 0;
}