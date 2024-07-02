#ifndef SATRS_GAMEWINDOW_H_
#define SATRS_GAMEWIND_H_

#include <string>

class GameWindow {
public:
	static bool init();
	static void quit();
	static void exitWithError(const std::string &message, bool doPopUp);
private:
};

#endif