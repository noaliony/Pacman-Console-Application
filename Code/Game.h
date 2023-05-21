#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Ghost.h"
#include <ctime>
#include "InputOutput.h"
#include <vector>
#include "Pacman.h"
#include "Fruit.h"
#include <string>
#define ESC 27

class Game 
{
	Board& m_boardGame;
	std::vector<Entity*> entitysArray;
	std::vector<Entity*> ::iterator ptr;
	bool m_gameOver;
	int m_amountBreadCrumbs;
	int m_modeGame;
public:
	Game(bool color, char gameDifficulty, Board& boardGame, int& score, int& lives, const std::string& inputMode);
	Game(const Game& other) = delete;
	Game& operator= (const Game& other) = delete;
	~Game();
	void startGame(bool& winSingleScreen,bool& lastScreen, int& score, int& lives);
private:
	void returnBoardToStartPosition();
	void waitForKey(Direction& keyFromTheUser, Direction& s);
	void updateNextCoordForPacman(Direction keyFromTheUser, Coordinate& currCoordPacman, Coordinate& nextCoordPacman, int rows, int cols);
	Direction isValidKey(char userSelection, Direction& dir);
	void updateAndPrintScoreAndLives();
	void ifGamePause(char& keyFromTheUser);
	void pacmanLoseOneLife();
	void gameOver(bool& winSingleScreen);
	bool checkIfPacmanAndGhostMeet(bool& winSingleScreen, bool& startAgain, std::fstream& fileResult);
	void checkIfPlayerWin(const int sumScoreForWin, bool& winSingleScreen, bool& startAgain, bool& lastScreen, std::fstream& fileResult);
	bool checkIfGhostAndFruitMeet();
	bool checkIfPacmanAndFruitMeet();
	bool checkIfEntitiesMeet(bool& winSingleScreen, bool& startAgain, std::fstream& fileResult);
	void updateModeGame(const std::string& inputMode);
	void getKeyFromFileSteps(std::fstream& fileSteps, Direction& keyFromTheUser, int i);
	void readFromFileSteps(std::fstream& fileSteps, int i, Direction& keyFromTheUser);
	void writeModeColorsToFile(std::fstream& fileSteps);
	void writeToFileWinOrLose(std::fstream& fileResult, const bool& winSingleScreen, const bool& startAgain);
	void openFiles(std::fstream& fileSteps, std::fstream& fileResult);
};
#endif 
