#ifndef ENTITY_H
#define ENTITY_H
#include "Board.h"

class Entity
{
private:
	Direction m_direction;
	char m_sign;
	int m_counterMove = 0;
protected:
	Coordinate m_currLocation; 
public:
	virtual ~Entity() {};
	const int& getCounterMove() { return m_counterMove; }
	void setDirection(Direction directionToChange) { m_direction = directionToChange; }
	void setSign(char signToChange) { m_sign = signToChange; }
	void setCurrLocation(Coordinate coord) { m_currLocation = coord; }
	Direction& getDirection() { return m_direction; }
	Coordinate& getCurrLocation() { return m_currLocation; }
	char getSign() { return m_sign; }
	virtual void move(Board& boardGame, const int& mode, std::fstream& fileSteps, int i) = 0;
	virtual const bool isValidMove(const Coordinate& nextCoord,const Board& boardGame) = 0;
	void counterUp() { m_counterMove++; }
	void counterReset() { m_counterMove = 0; }
	Coordinate coordInCurrDirection();
};

#endif 


