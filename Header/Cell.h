#ifndef CELL_H
#define CELL_H

#include "Coordinate.h"

class Cell
{
	Coordinate m_location;
	bool m_wall;
	bool m_food;
	bool m_pacman;
	bool m_ghost;
	bool m_empty;
	bool m_fruit;

public:
	Cell();
	void setLocation(Coordinate coord) { m_location = coord; }
	void setWall(bool wall) { m_wall = wall; }
	void setFood(bool food) { m_food = food; }
	void setPacman(bool pacman) { m_pacman = pacman; }
	void setGhost(bool ghost) { m_ghost = ghost;}
	void setEmpty(bool empty) { m_empty = empty; }
	void setFruit(bool fruit) { m_fruit = fruit; }

	const bool getWall() { return m_wall; }
	const bool getFood() { return m_food; }
	const bool getPacman() { return m_pacman; }
	const bool getGhost() { return m_ghost; }
	const bool getEmpty() { return m_empty; }
	const bool getFruit() { return m_fruit; }

	Coordinate getLocation() { return m_location; }
	char getSign();

};
#endif