#ifndef PACMAN_H
#define PACMAN_H
#include "Utils.h"
#include "Entity.h"

enum class pacmanStatus { DEATH = 0, MAX_LIVES = 3 };
class Pacman : public Entity
{
private:
	int m_lives;
	int m_coins;
	int m_breadCrumbEaten;
	Coordinate m_startLocation;

public:
	Pacman(Coordinate coord, int& score, int& lives);
	~Pacman() {};
	void setLives(const int livesToChange) { m_lives = livesToChange; }
	void setStartLocation(const Coordinate& coord) { m_startLocation = coord; }
	void setCoins(int coins) { m_coins = coins; }
	void setBreadCrumbEaten(int breadCrumbEaten) { m_breadCrumbEaten = breadCrumbEaten; }
	int getLives() const { return m_lives;}
	int getCoins() const { return m_coins;}
	int getBreadCrumbEaten() const { return m_breadCrumbEaten; }
	const Coordinate& getStartLocation() { return m_startLocation; }
	void move(Board& boardGame, const int& mode, std::fstream& fileSteps, int i);
	const bool isValidMove(const Coordinate& nextCoord,const Board& boardGame);
	void crossTheScreen(Coordinate& currCoord, Coordinate& nextCoord, const Direction direction, const int& rows, const int& cols);


};

#endif 


