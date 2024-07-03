#include "GameWindow.h"

#include <SDL.h>
#include <GL/glew.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <string>

// Some code from EndlessSky
namespace {
	SDL_Window* main_window = nullptr;
	SDL_GLContext gl_context = nullptr;
	int width = 640;
	int height = 320;

	bool checkSDLError() {
		std::string error_message = SDL_GetError();
		if (!error_message.empty()) 
		{
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

	// Info about display
	SDL_DisplayMode display_mode;
	if (SDL_GetCurrentDisplayMode(0, &display_mode))
	{
		return false;
	}

	int min_width = 640;
	int min_height = 320;
	int max_width = display_mode.w;
	int max_height = display_mode.h;
	if (max_width < min_width || max_height < min_height) {
		exitWithError("Unable to query monitor resolution.", true);
	}
	
	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
	main_window = SDL_CreateWindow("Soaring Above the Red Seas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
	if (!main_window) 
	{
		exitWithError("Failed to create window.", true);
	}

	// OpenGL Context Settings
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	gl_context = SDL_GL_CreateContext(main_window);
	if (!gl_context) 
	{
		exitWithError("Failed to create OpenGL 3.3 context!", true);
	}

	if (SDL_GL_MakeCurrent(main_window, gl_context)) 
	{
		exitWithError("Failed to set OpenGL context!", true);
	}

	// GlEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) 
	{
		exitWithError("Unable to initialize GLEW!", true);
	}

	//TODO: Guarantee version minimum 3.3
	return true;
}

// Cleanup
void GameWindow::quit() 
{
	SDL_ShowCursor(true);
	// Delete reverse order of construction
	if (gl_context)
		SDL_GL_DeleteContext(gl_context);
	if(main_window)
		SDL_DestroyWindow(main_window);
	SDL_Quit();
}

// Log error message and SDL error, then calls ::quit().
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

void GameWindow::swap() {
	SDL_GL_SwapWindow(main_window);
}