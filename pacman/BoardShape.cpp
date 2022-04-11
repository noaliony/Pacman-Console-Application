#include "BoardShape.h"

BoardShape::BoardShape()
{
	m_ghostCounter = m_legendCounter = m_pacmanCounter = 0;
}
//--------------------------------------------------------------------------------------------------------------------//
char BoardShape::getSignFromMatShape(int i, int j)
{
	return m_boardShape[i][j];
}
//--------------------------------------------------------------------------------------------------------------------//
void BoardShape::readFromFile(std::string fileName)
{
	std::ifstream file(fileName);
	char currLine[COLS];
	char ch;
	int j = 0, i;

	while (!file.eof())
	{
		ch = file.get();
		i = 0;
		while (ch != '\n' && !file.eof())
		{
			if (m_boardShape[j].size() < m_cols)
			{
				m_boardShape[j].push_back(ch);
				try{
					checkValidChar(ch);
				}
				catch(const char* strError){
					file.close();
					throw strError;
				}
			}
			i++;
			ch = file.get();
		}

		if (j == 0)
			m_cols = m_boardShape[j].size();
		else
			for (; i < m_cols; i++)
				m_boardShape[j].push_back(' ');
		j++;

	}
	m_rows = j;
	
	try {
		checkValidNumberOfEntities();
		updateLegend();
	}
	catch (const char* strError) {
		file.close();
		throw strError;
	}
	file.close();
}
//--------------------------------------------------------------------------------------------------------------------//
void BoardShape::updateLegend()
{
	bool found = false;
	int x = 0, y;

	for (y = 0; y < m_rows && !found; y++)
	{
		for (x = 0; x < m_cols && !found; x++)
			if (m_boardShape[y][x] == '&')
			{
				found = true;
			}
	}
	y--;
	x--;
	if (found)
	{
		m_scoreLocation = Coordinate(x, y);

		int difference = m_cols - x;
		if (y == 0 && difference < 20)
		{
			m_cols += 20 - difference;
			for (int i = 0; i < m_rows; i++)
			{
				std::string str_to_add;
				for (int j = 0; j < 20 - difference; j++)
					str_to_add.push_back(' ');
				m_boardShape[i].append(str_to_add);
			}
		}
		else if (y != 0 && difference < 20)
			throw "Sorry, this screen is invalid because there is no enough space for legend.";

		for (int i = y; i < y + 3; i++)
			for (int j = x; j < x + 20; j++)
				if (x + 20 < COLS)
				{
					m_boardShape[i][j] = '%';
				}
	}
}
//--------------------------------------------------------------------------------------------------------------------//
void BoardShape::checkValidChar(const char& ch)
{
	switch (ch)
	{
	case '@':
		m_pacmanCounter++;
		break;
	case '&':
		m_legendCounter++;
		break;
	case '$':
		m_ghostCounter++;
		break;
	case '#':
	case ' ':
	case '%':
		break;

	default:
		throw "Sorry, this screen is invalid because there is a invalid char.";
		break;
	}
}
void BoardShape::checkValidNumberOfEntities()
{
	if (m_pacmanCounter != 1)
		throw "Sorry, this screen is invalid because there are more than one pacman.";
	else if (m_ghostCounter > 4)
		throw "Sorry, this screen is invalid because there are more than four ghosts.";
	else if (m_legendCounter != 1)
		throw "Sorry, this screen is invalid because there are more than one legend.";
}