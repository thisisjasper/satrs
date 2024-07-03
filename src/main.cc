#include <iostream>
#include "GameWindow.h"

#include <SDL.h>
#include <GL/glew.h>
#include <spdlog/spdlog.h>

int main(int argc, char* argv[]) {
	spdlog::info("You are now playing: Soaring Above the Red Seas");
	GameWindow::init();

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		glClearColor(1.f, 1.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		GameWindow::swap();
	}

	GameWindow::quit();
	return 0;
}