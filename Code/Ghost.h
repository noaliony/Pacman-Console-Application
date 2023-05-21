#ifndef GHOST_H
#define GHOST_H
#include "Cell.h"
#include <stdlib.h>
#include "Entity.h"
#include"Utils.h"
#include <vector>
#include <algorithm>

class Ghost : public Entity
{
private:
	Coordinate m_startLocationGhost;
	std::vector<Direction> validDirections;
	bool m_bestGhost; 
	bool m_goodGhost;
	bool m_noviceGhost;
	int stopBeingSmart = 18 + rand() % 6;

public:
	Ghost() {}
	Ghost(Coordinate coord, int ghostLevel);
	~Ghost() {};

	const Coordinate& getStartLocation() { return m_startLocationGhost; }
	void setGhostLocation(Coordinate coord) {
		setCurrLocation(coord);
	}
	void move( Board& boardGame, const int& mode, std::fstream& fileSteps, int i);
	const bool isValidMove(const Coordinate& coord,const Board& boardGame);
private:
	void updateGhostMove(Coordinate& currCoord, Coordinate& nextCoord, Board& boardGame);
	void moveNovice(Coordinate& nextCoordGhost);
	void moveGood(Coordinate& nextCoordGhost, Board& boardGame);
	void moveBest(Coordinate& nextCoordGhost, Board& boardGame);
	void checkPossibleDirections(const Board& boardGame);
	bool isDirectionValid(Direction direction);

};
#endif 
