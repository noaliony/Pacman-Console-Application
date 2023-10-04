#include "Menu.h"

//--------------------------------------------------------------------------------------------------------------------//
void Menu::gameManager(int argc, char** argv)
{
	std::string inputMode;
	int i = 1;
	if (argc > 3)
	{
		throw "Error - there are too much args";
	}
	else if (argc == 3)
	{
		if (strcmp(argv[1], "-save") == 0 && strcmp(argv[2], "-silent") == 0) { argc--; }
		else if (strcmp(argv[1], "-load") == 0 && strcmp(argv[2], "-silent") == 0) { i++; }
		else
			throw "Error - the args are not correct";
	}
	else if (argc == 2)
	{
		if (strcmp(argv[1], "-save") == 0 || strcmp(argv[1], "-load") == 0) {}
		else
			throw "Error - the args are not correct";
	}
	else
	{
		inputMode = "regularGame";
	}

	if (argc > 1)
		inputMode = argv[i];
		
	try {
		menu(inputMode);
		if (inputMode == "-silent")
			std::cout << "test passed";
	}
	catch (bool)
	{
		std::cout << "test failed";
	}
}
//--------------------------------------------------------------------------------------------------------------------//
void Menu::menu(const std::string& inputMode)
{
	char userSelection = '0', gameDifficulty = '1';
	bool gameOn = true, winSingleScreen = false, lastScreen = false;
	if (inputMode != "-silent")
		InputOutput::printWelcome();
	std::vector<std::string> boardFileNames;
	int lives = (int)pacmanStatus::MAX_LIVES;
	int score = 0;
	int indexScreen = 0;

	getScreens(boardFileNames);
	if (inputMode == "-load" || inputMode == "-silent")
		userSelection = '1';
	while (gameOn)
	{
		if ((userSelection != '1') && (userSelection != '9') && (!winSingleScreen || userSelection == '0' || userSelection == '2' || userSelection == '7' || userSelection == '8'))
		{
			InputOutput::printMenu(m_color);
			userSelection = _getch();
			validUserSelection(userSelection);
		}

		if (userSelection == '1')
		{
			checkIfThereNoneScreen(boardFileNames, gameOn);
			if (gameOn)
			{
				winSingleScreen = false;
				(indexScreen + 1 == boardFileNames.size()) ? lastScreen = true : lastScreen = false;
				std::string str = boardFileNames[indexScreen];
				Board board(str);
				if (indexScreen == 0 && inputMode != "-load" && inputMode != "-silent")
					getDifficulty(gameDifficulty);
				try {
					Game(m_color, gameDifficulty, board, score, lives, inputMode).startGame(winSingleScreen, lastScreen, score, lives);
					system("cls");
					m_gamePlayed = true;

					if (winSingleScreen)
						indexScreen++;
					else
					{
						 if (inputMode == "-load")
							userSelection = '9';
						else if (inputMode == "-silent")
							gameOn = false;
						else
						{
							userSelection = '0';
							indexScreen = 0;
							score = 0;
							lives = 3;
						}
					}

				}
				catch (const char* strError) {
					indexScreen++;
					if (indexScreen == boardFileNames.size() && !m_gamePlayed)
					{
						std::cout << "Sorry, there is no valid screens";
						userSelection = '9';
					}
				}

			}
		}
		else if (userSelection == '2')
		{
			checkIfThereNoneScreen(boardFileNames, gameOn);
			if (gameOn)
			{
				lastScreen = false;
				InputOutput::printChooseFiles(boardFileNames);
				indexScreen = _getch() - 1 - '0';
				checkValidityInputIndexScreen(indexScreen, boardFileNames.size());
				std::string str = boardFileNames[indexScreen];
				Board board(str);
				getDifficulty(gameDifficulty);
				try {
					Game(m_color, gameDifficulty, board, score, lives, inputMode).startGame(winSingleScreen, lastScreen, score, lives);
					m_gamePlayed = true;
					system("cls");
					indexScreen = 0;
					score = 0;
					lives = 3;
				}
				catch (const char* strError) {
					std::cout << strError;
					char ch;
					pressCharToReturnMenu(ch);
				}

			}
		}
		else if (userSelection == '7')
		{
			m_color = !m_color;
			if (!m_color)
				setTextColor(Color::WHITE);
		}
		else if (userSelection == '8')
		{
			char ch;
			InputOutput::printInstructionsAndKeys();
			pressCharToReturnMenu(ch);
		}
		else if (userSelection == '9')
		{
			gameOn = false;
			InputOutput::printGoodBye();
			continue;
		}

		if (indexScreen == boardFileNames.size() && m_gamePlayed)
		{
			if (inputMode != "-silent")
				InputOutput::printWinInAllScreens();
			userSelection = '0';

			if (inputMode == "regularGame" || inputMode == "-save")
				indexScreen = 0;
			else if (inputMode == "-load")
				userSelection = '9';
			else if (inputMode == "-silent")
				gameOn = false;
		}

	}
}

void Menu::getDifficulty(char& gameDifficulty)
{
	system("cls");
	InputOutput::printGhostLevel();
	gameDifficulty = _getch();
	validUserSelectionForGhost(gameDifficulty);
}
//--------------------------------------------------------------------------------------------------------------------//

void Menu::checkValidityInputIndexScreen(int& indexScreen, int size)
{
	while (indexScreen >= size)
	{
		std::cout << "Please choose a valid input" << std::endl << std::endl;
		indexScreen = _getch() - 1 - '0';
	}
	system("cls");
}

//--------------------------------------------------------------------------------------------------------------------//
void Menu::validUserSelection(char& userSelection)
{
	while (userSelection != '1' && userSelection != '2' && userSelection != '7' && userSelection != '8' && userSelection != '9')
	{
		std::cout << "Please choose a valid input" << std::endl << std::endl;
		userSelection = _getch();
	}
	system("cls");
}
//--------------------------------------------------------------------------------------------------------------------//
void Menu::pressCharToReturnMenu(char& ch)
{
	std::cout << std::endl;

	std::cout << "Please press any key to return to the main menu" << std::endl;
	while (!_kbhit())
		Sleep(500);
	ch = getKey();
	system("cls");
}
//--------------------------------------------------------------------------------------------------//
void Menu::validUserSelectionForGhost(char& gameDifficulty)
{
	while (gameDifficulty != '1' && gameDifficulty != '2' && gameDifficulty != '3')
	{
		std::cout << "Please choose a valid input" << std::endl << std::endl;
		gameDifficulty = _getch();
	}
	system("cls");
}
//--------------------------------------------------------------------------------------------------------------------//

void Menu::getScreens(std::vector<std::string> &boardFileNames)
{
	for (const auto& entry : fs::directory_iterator(fs::current_path()))
	{
		if (entry.is_regular_file() && (entry.path().extension().string().compare(".screen") == 0))
			boardFileNames.push_back(entry.path().filename().string());
	}
}
//--------------------------------------------------------------------------------------------------------------------//
void Menu::checkIfThereNoneScreen(std::vector<std::string>& boardFileNames, bool& gameOn)
{
	if (boardFileNames.empty())
	{
		gameOn = false;
		std::cout << "Sorry, there is no screens in this file";
		Sleep(2000);
		system("cls");
		InputOutput::printGoodBye();
	}
}
//--------------------------------------------------------------------------------------------------------------------//

