#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string.h>
#include "BoardShape.h"
#include "Cell.h"
#include "InputOutput.h"
#include "Coordinate.h"
#include <vector>

enum class Direction { 
	LEFT = 'A',
	RIGHT = 'D',
	UP = 'W',
	DOWN = 'X',
	STAY = 'S'
};
enum class Mode { Regular, Save, Load, Silent };

class Board
{

private:
	int m_rows;
	int m_cols;
	Cell** m_boardCells;
	bool m_color;
	Coordinate m_coordPacman;
	std::vector<Coordinate> coordGhosts;
	Coordinate m_scoreLocation;
	std::string m_fileName;

public:
	Board(const std::string& fileName);
	~Board();
	Board(const Board& other) = delete;
	Board& operator= (const Board& other) = delete;

	void setPacman(const Coordinate& coord, bool value = true);
	void setGhost(const Coordinate& coord, bool value = true);
	void setFood(const Coordinate& coord, bool value = true);
	void setWall(const Coordinate& coord, bool value = true);
	void setEmpty(const Coordinate& coord, bool value = true);
	void setFruit(const Coordinate& coord, bool value = true);
	void setRows(const int rows) { m_rows = rows; }
	void setCols(const int cols) { m_cols = cols; }
	void setScoreLocation(const Coordinate& scoreLocation) { m_scoreLocation = scoreLocation; }
	void setColorMode(const bool& colorMode = true) { m_color = colorMode;}

	const bool getEmpty(const Coordinate& coord) const { return m_boardCells[coord.getCoordY()][coord.getCoordX()].getEmpty(); }
	const bool getFood(const Coordinate& coord) const  { return m_boardCells[coord.getCoordY()][coord.getCoordX()].getFood(); }
	const bool getWall(const Coordinate& coord) const { return m_boardCells[coord.getCoordY()][coord.getCoordX()].getWall(); }
	const bool getPacman(const Coordinate& coord) const { return m_boardCells[coord.getCoordY()][coord.getCoordX()].getPacman(); }
	const bool getGhost(const Coordinate& coord) const { return m_boardCells[coord.getCoordY()][coord.getCoordX()].getGhost(); }
	const bool getFruit(const Coordinate& coord) const { return m_boardCells[coord.getCoordY()][coord.getCoordX()].getFruit(); }
	std::vector<Coordinate> getCoordGhosts() const { return coordGhosts; }
	const bool getColorMode() const { return m_color; }
	int getRows() const { return m_rows; }
	int getCols() const { return m_cols; }
	Coordinate getScoreLocation() { return m_scoreLocation; }
	std::string getFileName() const {return m_fileName ;}

	Coordinate& getCoordPacman() { return m_coordPacman; }
	int initBoard();
	void changeColorMode(const bool color) { m_color = color; };
	void printCell(const Coordinate& currCoord, char valFruit);
    void printBoard();

private:
	void updateEmptyCell(const Coordinate& coord, bool value);
	bool isEmptyCell(const Coordinate& coord);
};

#endif