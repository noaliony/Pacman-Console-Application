#include "Entity.h"

Coordinate Entity::coordInCurrDirection()
{
	Coordinate nextCoord = getCurrLocation();
	switch (getDirection())
	{
	case Direction::LEFT:
		nextCoord.setCoordX(nextCoord.getCoordX() - 1);
		break;
	case Direction::RIGHT:
		nextCoord.setCoordX(nextCoord.getCoordX() + 1);
		break;
	case Direction::UP:
		nextCoord.setCoordY(nextCoord.getCoordY() - 1);
		break;
	case Direction::DOWN:
		nextCoord.setCoordY(nextCoord.getCoordY() + 1);
		break;
	}

	return nextCoord;
}