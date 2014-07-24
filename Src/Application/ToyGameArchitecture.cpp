#include "Classic/Application.h"

int main(int argc, char **argv) {
	// build the application
	Classic::CApplication &application = Classic::CApplication::getInstance();

	// initialize it and run if initialization was successful
	if(application.initialize()) {
		application.run();
	}

	// finally, destroy the application
	application.release();

	return 0;
}