#include "Game.h"


//--------------------------------------------------------------------------------------------------------------------//
Game::Game(bool color, char gameDifficulty, Board& boardGame, int& score, int& lives, const std::string& inputMode) : m_boardGame(boardGame)
{
	srand(time(NULL));
	try {
		m_amountBreadCrumbs = m_boardGame.initBoard();
	}
	catch (const char* strError) {
		throw strError;
	}
	entitysArray.push_back(new Pacman(m_boardGame.getCoordPacman(), score, lives));
	entitysArray.push_back(new Fruit());
	for (int i = 0; i < m_boardGame.getCoordGhosts().size(); ++i)
		entitysArray.push_back(new Ghost((m_boardGame.getCoordGhosts())[i], gameDifficulty - '0'));
	m_boardGame.changeColorMode(color);
	m_gameOver = false;
	updateModeGame(inputMode);
}
//--------------------------------------------------------------------------------------------------------------------//
Game::~Game()
{
	int size = entitysArray.size();
	for (int i = 0; i < size; i++)
		delete entitysArray[i];
}
//--------------------------------------------------------------------------------------------------------------------//
void Game::startGame(bool& winSingleScreen,bool& lastScreen, int& score, int& lives)
{
	char userSelection;
	Direction keyFromTheUser, s = Direction::STAY;
	bool startAgain, entitiesMeet;
	int counterPacmanMove;
	std::fstream fileSteps;
	std::fstream fileResult;
	char currLine[30];

	try {
		openFiles(fileSteps, fileResult);

		writeModeColorsToFile(fileSteps);
		
		if(m_modeGame == (int)Mode::Load || m_modeGame == (int)Mode::Silent)
		{
			fileSteps.getline(currLine, 30, '\n');
			if (strcmp(currLine, "The game is with colors") == 0)
				m_boardGame.setColorMode();
		}

		if (m_modeGame != (int)Mode::Silent)
			m_boardGame.printBoard();
		updateAndPrintScoreAndLives();

		if (m_modeGame == (int)Mode::Save || m_modeGame == (int)Mode::Regular)
			waitForKey(keyFromTheUser, s);

		while (!m_gameOver)
		{
			startAgain = false;
			if (m_modeGame == (int)Mode::Save || m_modeGame == (int)Mode::Regular)
				Sleep(300);
			else if (m_modeGame == (int)Mode::Load)
				Sleep(100);

			if (m_modeGame == (int)Mode::Save || m_modeGame == (int)Mode::Regular)
				entitysArray[0]->setDirection(keyFromTheUser);

			counterPacmanMove = entitysArray[0]->getCounterMove();

			int size = entitysArray.size();
			for (int i = 0; !startAgain && i < size; i++)
			{
				readFromFileSteps(fileSteps, i, keyFromTheUser);
				
				if (typeid(*(entitysArray[i])) == typeid(Pacman) || (typeid(*(entitysArray[i])) == typeid(Ghost) && (counterPacmanMove + 1) % 2 == 0) || (typeid(*(entitysArray[i])) == typeid(Fruit) && (counterPacmanMove + 1) % 3 == 0))
				{
					(entitysArray[i])->move(m_boardGame, m_modeGame, fileSteps, i);
					entitiesMeet = checkIfEntitiesMeet(winSingleScreen, startAgain, fileResult);
					if (entitiesMeet && m_modeGame == (int)Mode::Save)
					{
						if (((Fruit*)(entitysArray[i]))->getAppearance() == true)
							fileSteps << "fruit die" << std::endl;
					}
					if (((Pacman*)entitysArray[0])->getLives() != 0)
						updateAndPrintScoreAndLives();

				}
				if (!startAgain)
					checkIfPlayerWin(m_amountBreadCrumbs, winSingleScreen, startAgain, lastScreen, fileResult);

				writeToFileWinOrLose(fileResult, winSingleScreen, startAgain);
			
			}
			if (m_modeGame == (int)Mode::Save || m_modeGame == (int)Mode::Regular)
			{
				if (_kbhit())
				{
					userSelection = getKey();
					ifGamePause(userSelection);
					keyFromTheUser = isValidKey(userSelection, entitysArray[0]->getDirection());
				}
			}
		}
		fileSteps.close();
		fileResult.close();
		score = ((Pacman*)entitysArray[0])->getCoins();
		lives = ((Pacman*)entitysArray[0])->getLives();

	}
	catch (const char* error)
	{
			std::cout << error;
	}
}
//--------------------------------------------------------------------------------------------------------------------//
void Game::getKeyFromFileSteps(std::fstream& fileSteps, Direction& keyFromTheUser, int i)
{
	fileSteps.seekg(1, std::ios::cur); /* 1 = for read ':' */
	keyFromTheUser = (Direction)fileSteps.get();
	entitysArray[i]->setDirection(keyFromTheUser);
	fileSteps.get();
}
//--------------------------------------------------------------------------------------------------------------------//
void Game::checkIfPlayerWin(const int amountBreadCrumbs, bool& winSingleScreen, bool& startAgain, bool& lastScreen, std::fstream& fileResult)
{ 
	if (((Pacman*)entitysArray[0])->getBreadCrumbEaten() == amountBreadCrumbs)
	{
		m_gameOver = true;
		if (m_modeGame != (int)Mode::Silent)
		{
			Sleep(1000);
			system("cls");
			if (!lastScreen)
				InputOutput::printWin();
		}
		else
		{
			std::string str;
			getline(fileResult, str);
			std::stringstream sstream(str);
			int num;
			std::string temp;
			sstream >> temp;
			sstream >> num;

			if (((Pacman*)entitysArray[0])->getCounterMove() != num || temp != "win:")
				throw false;
		}
		returnBoardToStartPosition();
		winSingleScreen = true;
		startAgain = true;
	}
}
//--------------------------------------------------------------------------------------------------------------------//
bool Game::checkIfEntitiesMeet(bool& winSingleScreen, bool& startAgain, std::fstream& fileResult)
{
	return (checkIfGhostAndFruitMeet() || checkIfPacmanAndFruitMeet() || checkIfPacmanAndGhostMeet(winSingleScreen, startAgain, fileResult));
}
//--------------------------------------------------------------------------------------------------------------------//
void Game::updateModeGame(const std::string& inputMode)
{
	if (inputMode == "regularGame")
		m_modeGame = (int)Mode::Regular;
	else if (inputMode == "-save")
		m_modeGame = (int)Mode::Save;
	else if (inputMode == "-load")
		m_modeGame = (int)Mode::Load;
	else if (inputMode == "-silent")
		m_modeGame = (int)Mode::Silent;
}

//--------------------------------------------------------------------------------------------------------------------//
bool Game::checkIfPacmanAndGhostMeet(bool& winSingleScreen, bool& startAgain, std::fstream& fileResult)
{
	int size = entitysArray.size();
	int lives = ((Pacman*)entitysArray[0])->getLives();

	for (int i = 2; i < size; i++)
	{
		if (m_boardGame.getPacman(entitysArray[i]->getCurrLocation()) || m_boardGame.getGhost(entitysArray[0]->getCurrLocation()))
		{
			startAgain = true;
			((Pacman*)entitysArray[0])->setLives(lives - 1);

			if (m_modeGame == (int)Mode::Silent)
			{
				std::string str;
				getline(fileResult, str);
				std::stringstream sstream(str);
				int num;
				std::string temp;
				sstream >> temp;
				sstream >> num;

				if (((Pacman*)entitysArray[0])->getCounterMove() != num || temp != "lose:")
					throw false;
			}

			if (lives != 1)
				pacmanLoseOneLife();
			else
				gameOver(winSingleScreen);
			
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------------------------------------------------//
bool Game::checkIfGhostAndFruitMeet()
{
	Fruit* pF = dynamic_cast<Fruit*>(entitysArray[1]);

	if (pF && pF->getAppearance())
	{
		if (m_boardGame.getGhost(entitysArray[1]->getCurrLocation()) && m_boardGame.getFruit(entitysArray[1]->getCurrLocation()))
		{
			pF->FruitLeaveTheGame(entitysArray[1]->getCurrLocation(), m_boardGame, m_modeGame);
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------------------------------------------------------------//
void Game::pacmanLoseOneLife()
{
	returnBoardToStartPosition();
	if (m_modeGame!= (int)Mode::Silent)
	{
		Sleep(1500);
		system("cls");
		m_boardGame.printBoard();
		updateAndPrintScoreAndLives();
		gotoxy(((Pacman*)entitysArray[0])->getStartLocation().getCoordX(), ((Pacman*)entitysArray[0])->getStartLocation().getCoordY());
	}
}
//--------------------------------------------------------------------------------------------------------------------//

void Game::returnBoardToStartPosition()
{
	for (int i = 0; i < m_boardGame.getRows(); i++) {
		for (int j = 0; j < m_boardGame.getCols(); j++) {
			m_boardGame.setPacman(Coordinate(j, i), false);
		}
	}
	m_boardGame.setPacman(((Pacman*)entitysArray[0])->getStartLocation()); //default = true
	(entitysArray[0])->setCurrLocation(((Pacman*)entitysArray[0])->getStartLocation());

	for (ptr = entitysArray.begin() + 2; ptr != entitysArray.end(); ++ptr)
	{
		m_boardGame.setGhost((*ptr)->getCurrLocation(), false);
		m_boardGame.setGhost(((Ghost*)(*ptr))->getStartLocation());
		(*ptr)->setCurrLocation(((Ghost*)(*ptr))->getStartLocation());
		if (m_modeGame == (int)Mode::Load)
			(*ptr)->setDirection(Direction::STAY);

	}
	if (((Fruit*)(entitysArray[1]))->getAppearance())
		((Fruit*)(entitysArray[1]))->FruitLeaveTheGame((entitysArray[1])->getCurrLocation(), m_boardGame, m_modeGame);
}
//--------------------------------------------------------------------------------------------------------------------//
void Game::gameOver(bool& winSingleScreen)
{
	m_gameOver = true;
	winSingleScreen = false;
	if (m_modeGame != (int)Mode::Silent)
	{
		Sleep(1500);
		system("cls");
		InputOutput::printGameOver();
	}

}

//--------------------------------------------------------------------------------------------------------------------//
void Game::waitForKey(Direction& keyFromTheUser, Direction& s)
{
	char userSelection;
	while (!_kbhit())
		Sleep(500);
	userSelection = getKey();
	keyFromTheUser = isValidKey(userSelection, s);

}
//--------------------------------------------------------------------------------------------------------------------//
void Game::updateNextCoordForPacman(Direction keyFromTheUser, Coordinate& currCoordPacman, Coordinate& nextCoordPacman, int rows, int cols)
{
	entitysArray[0]->setDirection(keyFromTheUser);
}
//--------------------------------------------------------------------------------------------------------------------//
Direction Game::isValidKey(char userSelection, Direction& dir)
{
	if (userSelection == ESC)
		return dir;
	char us = toupper(userSelection);
	switch (us)
	{
	case (char)Direction::LEFT:
		return Direction::LEFT;
		break;
	case (char)Direction::RIGHT:
		return Direction::RIGHT;
		break;
	case (char)Direction::UP:
		return Direction::UP;
		break;
	case (char)Direction::DOWN:
		return Direction::DOWN;
		break;
	case (char)Direction::STAY:
		return Direction::STAY;
		break;
	default:
		return dir;
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------//

void Game::updateAndPrintScoreAndLives()
{
	if (m_modeGame != (int)Mode::Silent)
	{
		Coordinate scoreLocation = m_boardGame.getScoreLocation();

		if (m_boardGame.getColorMode())
			setTextColor(Color::CYAN);

		gotoxy(scoreLocation.getCoordX(), scoreLocation.getCoordY());
		std::cout << "Your score: " << ((Pacman*)entitysArray[0])->getCoins() << std::endl;
		gotoxy(scoreLocation.getCoordX(), scoreLocation.getCoordY() + 1);
		std::cout << "Your lives: " << ((Pacman*)entitysArray[0])->getLives() << std::endl;
		gotoxy(scoreLocation.getCoordX(), scoreLocation.getCoordY() + 2);
	}
}
//--------------------------------------------------------------------------------------------------------------------//
void Game::ifGamePause(char& keyFromTheUser)
{
	if (keyFromTheUser == ESC) {
		while (!_kbhit() || _getch() != ESC)
			Sleep(500);
	}
}
//--------------------------------------------------------------------------------------------------------------------//

bool Game::checkIfPacmanAndFruitMeet()
{
	if (((Fruit*)(entitysArray[1]))->getAppearance())
	{
		if (entitysArray[0]->getCurrLocation().compareCoords(entitysArray[1]->getCurrLocation()) && m_boardGame.getFruit(entitysArray[0]->getCurrLocation()))
		{
			Fruit* pF = dynamic_cast<Fruit*>(entitysArray[1]);
			Pacman* pP = dynamic_cast<Pacman*>(entitysArray[0]);
			if (pF && pP)
			{
				pP->setCoins(pP->getCoins() + pF->getValDigit());
				pF->FruitLeaveTheGame(entitysArray[1]->getCurrLocation(), m_boardGame, m_modeGame);
				return true;
			}

		}
	}
	return false;
}
//--------------------------------------------------------------------------------------------------------------------//
void Game::readFromFileSteps(std::fstream& fileSteps, int i, Direction& keyFromTheUser)
{
	if (m_modeGame == (int)Mode::Load || m_modeGame == (int)Mode::Silent)
	{
		char ch = fileSteps.get();
		if (i == ch - '0')
		{
			getKeyFromFileSteps(fileSteps, keyFromTheUser, i);
			char currLine[30] = {};
			if (i == 1)
				((Fruit*)(entitysArray[i]))->function(fileSteps, m_boardGame, currLine, m_modeGame);
		}
		else
		{
			fileSteps.seekg(-1, std::ios::cur); /* move the cursor one step left */
			if (ch == 'f')
			{
				char currLine[30] = {};
				fileSteps.getline(currLine, 30, '\n');

				((Fruit*)(entitysArray[1]))->function(fileSteps, m_boardGame, currLine, m_modeGame);
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------//
void Game::writeModeColorsToFile(std::fstream& fileSteps)
{
	if (m_modeGame == (int)Mode::Save)
	{
		if (m_boardGame.getColorMode())
			fileSteps << "The game is with colors" << std::endl;
		else
			fileSteps << "The game is without colors" << std::endl;
	}
}
//--------------------------------------------------------------------------------------------------------------------//
void Game::writeToFileWinOrLose(std::fstream& fileResult, const bool& winSingleScreen, const bool& startAgain)
{
	if (m_modeGame == (int)Mode::Save)
	{
		if (winSingleScreen)
			fileResult << "win: " << entitysArray[0]->getCounterMove() << std::endl;
		else if (startAgain)
			fileResult << "lose: " << entitysArray[0]->getCounterMove() << std::endl;
	}
}
//--------------------------------------------------------------------------------------------------------------------//
void Game::openFiles(std::fstream& fileSteps, std::fstream& fileResult)
{
	std::string str = m_boardGame.getFileName();
	std::string resultFile, stepsFile;
	int len = str.size() - 6;
	str.erase(str.begin() + len, str.end());
	resultFile = str + "result";
	stepsFile = str + "steps";

	if (m_modeGame == (int)Mode::Load || m_modeGame == (int)Mode::Silent)
	{
		fileSteps.open(stepsFile, std::ios::in);
		fileResult.open(resultFile, std::ios::in);
	}
	else if(m_modeGame != (int)Mode::Regular)
	{
		fileSteps.open(stepsFile, std::ios::out | std::ios::trunc);
		fileResult.open(resultFile, std::ios::out | std::ios::trunc);
	}
	if (m_modeGame != (int)Mode::Regular)
	{
		if (!fileSteps.is_open())
			throw "no file steps";
		if (!fileResult.is_open())
			throw "no file result";
	}
}