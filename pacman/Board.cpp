#include "Board.h"
//------------------------------------------------------------------------------------------------------------------------------//
/* build the matrix of cells*/
Board::Board(const std::string& fileName)
{
	m_boardCells = new Cell * [BoardShape::ROWS];

	for (int i = 0; i < BoardShape::ROWS; i++)
	{
		m_boardCells[i] = new Cell[BoardShape::COLS];
	}
	m_fileName = fileName;
}

//--------------------------------------------------------------------------------------------------------------------//
Board::~Board()
{
	for (int i = 0; i < BoardShape::ROWS; i++)
	{
		delete[] m_boardCells[i];
	}
	delete[] m_boardCells;
}

//--------------------------------------------------------------------------------------------------------------------//
void Board::setPacman(const Coordinate& coord, bool value)
{
	m_boardCells[coord.getCoordY()][coord.getCoordX()].setPacman(value);
	updateEmptyCell(coord, value);
	if (value)
		m_coordPacman = coord;
}
//--------------------------------------------------------------------------------------------------------------------//

void Board::setGhost(const Coordinate& coord, bool value)
{
	m_boardCells[coord.getCoordY()][coord.getCoordX()].setGhost(value);
	updateEmptyCell(coord, value);
}
//--------------------------------------------------------------------------------------------------------------------//
void Board::setFood(const Coordinate& coord, bool value)
{
	m_boardCells[coord.getCoordY()][coord.getCoordX()].setFood(value);
	updateEmptyCell(coord, value);
}
//--------------------------------------------------------------------------------------------------------------------//
void Board::setWall(const Coordinate& coord, bool value)
{
	m_boardCells[coord.getCoordY()][coord.getCoordX()].setWall(value);
	updateEmptyCell(coord, value);
}
//--------------------------------------------------------------------------------------------------------------------//
void Board::setEmpty(const Coordinate& coord, bool value)
{
	m_boardCells[coord.getCoordY()][coord.getCoordX()].setEmpty(value);
}
//--------------------------------------------------------------------------------------------------------------------//
void Board::setFruit(const Coordinate& coord, bool value)
{
	m_boardCells[coord.getCoordY()][coord.getCoordX()].setFruit(value);
	updateEmptyCell(coord, value);
}
//--------------------------------------------------------------------------------------------------------------------//
void Board::updateEmptyCell(const Coordinate& coord, bool value)
{
	if (value)
		setEmpty(coord, false);
	else
	{
		if (isEmptyCell(coord))
			setEmpty(coord); //default = true;
		else
			setEmpty(coord, false);
	}
}
//--------------------------------------------------------------------------------------------------------------------//
bool Board:: isEmptyCell(const Coordinate& coord)
{
	Cell& cell = m_boardCells[coord.getCoordY()][coord.getCoordX()];
	if (!cell.getFood() && !cell.getGhost() && !cell.getPacman() && !cell.getWall())
		return true;
	return false;
}
//--------------------------------------------------------------------------------------------------------------------//
int Board::initBoard()
{
	char ch;
	BoardShape b;
	try {
		b.readFromFile(m_fileName);
	}
	catch (const char* strError) {
		throw strError;
	}
	
	Coordinate coord;
	int counterFood = 0;

	setScoreLocation(b.getScortLocation());
	setRows(b.getRows());
	setCols(b.getCols());

	for (int i = 0; i < b.getRows(); i++)
	{
		for (int j = 0; j < b.getCols(); j++)
		{
			coord.setCoordX(j);
			coord.setCoordY(i);
			ch = b.getSignFromMatShape(i, j);
			m_boardCells[i][j].setLocation(coord);

			switch (ch)
			{
			case '#':
				setWall(coord);
				break;

			case ' ':				
				setFood(coord);
				counterFood++;
				break;

			case '%':
				setEmpty(coord);
				break;

			case '@':
				setPacman(coord);
				m_coordPacman = coord;
				break;

			case '$':
				setGhost(coord);
				coordGhosts.push_back(coord);
				break;
			}
		}
	}
	return counterFood;
}

//--------------------------------------------------------------------------------------------------------------------//

void Board::printCell(const Coordinate& currCoord, char valFruit)
{
	if (valFruit == '0')
		InputOutput::printChar(currCoord, m_boardCells[currCoord.getCoordY()][currCoord.getCoordX()].getSign(), m_color);
	else
		InputOutput::printChar(currCoord, valFruit, m_color);
}
//--------------------------------------------------------------------------------------------------------------------//

void Board::printBoard()
{
	Coordinate coord;
	InputOutput::printReady();

	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			coord.setCoordX(j);
			coord.setCoordY(i);
			printCell(coord, '0');
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------//
