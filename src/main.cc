#include <iostream>
#include "GameWindow.h"

#include <SDL.h>
#include <spdlog/spdlog.h>

int main(int argc, char* args[]) {
	spdlog::info("You are now playing: Soaring Above the Red Seas");
	GameWindow::init();
	return 0;
}