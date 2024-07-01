#include "GameWindow.h"

#include <SDL.h>
#include <spdlog/spdlog.h>

#include <iostream>

// Inspired by EndlessSky
namespace {
	SDL_Window* main_window = nullptr;
	SDL_GLContext gl_context = nullptr;
	int width = 640;
	int height = 320;

	bool checkSDLError() {
		std::string error_message = SDL_GetError();
		if (!error_message.empty()) {
		
			return true;
		}
		return false;
	}
}

bool GameWindow::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		checkSDLError();
		return false;
	}
	main_window = SDL_CreateWindow("Soaring Above the Red Seas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
	}
	SDL_DestroyWindow(main_window);
	SDL_Quit();
	return true;
}

void GameWindow::quit() {

}

void GameWindow::exitWithError()
{
}
