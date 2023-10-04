#include "Coordinate.h"

bool Coordinate::compareCoords(const Coordinate& coordToCompare) const
{
	return m_x == coordToCompare.getCoordX() && m_y == coordToCompare.getCoordY();
}