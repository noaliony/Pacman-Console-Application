#ifndef BOARDSHAPE_H
#define BOARDSHAPE_H
#include "Utils.h"
#include <fstream>
#include "Coordinate.h"

class BoardShape
{
public:
	BoardShape();
	enum BoundBoard { ROWS =25, COLS = 80 };
	char getSignFromMatShape(int i, int j);
	void readFromFile(std::string fileName);
	int getRows() const { return m_rows; }
	int getCols() const { return m_cols; }
	Coordinate getScortLocation() const { return m_scoreLocation; }
	void checkValidChar(const char& ch);
	void checkValidNumberOfEntities();

private:
	std::string m_boardShape[ROWS];
	int m_rows;
	int m_cols = COLS;
	Coordinate m_scoreLocation;
	int m_pacmanCounter;
	int m_ghostCounter;
	int m_legendCounter;

	void updateLegend();
};

#endif
