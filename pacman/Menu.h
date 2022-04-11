#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Game.h"
#include <filesystem>

namespace fs = std::filesystem;

class Menu
{
private:
	int userSelection;
	bool m_color = false;
	bool m_gamePlayed = false;

public:
	void gameManager(int argc, char** argv);
private:	
	void menu(const std::string& inputMode);
	void validUserSelection(char& userSelection);
	void pressCharToReturnMenu(char& ch);
	void validUserSelectionForGhost(char& gameDifficulty);
	void getScreens(std::vector<std::string> &boardFileNames);
	void checkIfThereNoneScreen(std::vector<std::string>& boardFileNames, bool& gameOn);
	void getDifficulty(char& gameDifficulty);
	void checkValidityInputIndexScreen(int& indexScreen, int size);
};

#endif