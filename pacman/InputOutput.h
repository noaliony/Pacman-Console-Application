#ifndef INPUT_OUTPUT
#define INPUT_OUTPUT
#include "Utils.h"
#include "Coordinate.h"
#include <vector>

enum class CenterScreen { centerX = 23, centerY = 8 };

class InputOutput{
	
public:
	static void printGameOver();
	static void printWin();
	static void printWinInAllScreens();
	static void printWelcome();
	static void printGoodBye();
	static void printMenu(bool color);
	static void printInstructionsAndKeys();
	static void printReady();
	static void printChar(Coordinate coord, char sign, bool color); 
	static void printGhostLevel();
	static void printChooseFiles(std::vector<std::string> boardFileNames);
};


#endif 

