#include "GameWindow.h"

#include <SDL.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <string>

// Inspired by EndlessSky
namespace {
	SDL_Window* main_window = nullptr;
	SDL_GLContext gl_context = nullptr;
	int width = 640;
	int height = 320;

	bool checkSDLError() {
		std::string error_message = SDL_GetError();
		if (!error_message.empty()) {
			spdlog::error("SDL2 Error: " + error_message);
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
	if (!main_window) {
		GameWindow::exitWithError("Failed to create window.", true);
	}

	// OpenGL Context Settings
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


	// GlEW
	

	return true;
}

void GameWindow::quit() 
{
	SDL_DestroyWindow(main_window);
	checkSDLError();
	SDL_Quit();
}

void GameWindow::exitWithError(const std::string &message, bool doPopUp)
{
	spdlog::error(message);
	checkSDLError();
	
	if (doPopUp) 
	{
		SDL_MessageBoxData box;
		box.flags = SDL_MESSAGEBOX_ERROR;
		box.window = nullptr;
		box.title = "Soaring Above the Red Seas: ERROR";
		box.message = message.c_str();
		box.colorScheme = nullptr;

		SDL_MessageBoxButtonData button;
		button.flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
		button.buttonid = 0;
		button.text = "OK";
		box.numbuttons = 1;
		box.buttons = &button;

		int result = 0;
		SDL_ShowMessageBox(&box, &result);
	}

	GameWindow::quit();	
}
