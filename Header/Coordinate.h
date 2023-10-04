#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
	int m_x;
	int m_y;

public:
	Coordinate() {};
	Coordinate(int x, int y) :m_x(x), m_y(y) {};
	const int getCoordX() const { return m_x; }
	const int getCoordY() const { return m_y; }
	void setCoordX (int x) { m_x = x; }
	void setCoordY (int y) { m_y = y; }
	bool compareCoords(const Coordinate& coordToCompare) const;
};
#endif 