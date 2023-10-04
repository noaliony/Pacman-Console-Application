#include "Cell.h"

Cell::Cell()
{
	m_wall = m_empty = m_food = m_pacman = m_ghost = m_fruit = false;
}
char Cell::getSign()
{
	if (getEmpty())
		return ' ';
	else if (getGhost())
		return '$';
	else if (getPacman())
		return '@';
	else if (getFood())
		return '.';
	else if (getWall())
		return '#';
}


