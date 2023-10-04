#ifndef FRUIT_H
#define FRUIT_H
#include "Entity.h"
#include <fstream>
#include <sstream>

enum class randDir { left, right, up, down, stay }; // In the enum of the direction we have placement to letter and because of this we created another enum to the ghost and fruit

class Fruit : public Entity
{
	int m_valDigit;
	bool m_fruitAppear;
	int m_fruitLifeTime;
	int m_amountStepWithoutFruit;
public:
	Fruit();
	~Fruit() {};
	void setAppearance(bool isAppear) { m_fruitAppear = isAppear; }
	void setAmountStepWithoutFruit(int amount) { m_amountStepWithoutFruit = amount; }
	void setValDigit(int valDigit) { m_valDigit = valDigit; }
	int getValDigit() const { return m_valDigit; } 
	int getFruitLifeTime() const { return m_fruitLifeTime; }
	bool getAppearance() const { return m_fruitAppear; }
	void move(Board& boardGame, const int& mode, std::fstream& fileSteps, int i);
	const bool isValidMove(const Coordinate& coord,const Board& boardGame);
	void updateFruitMove(Coordinate& currCoord, Coordinate& nextCoord, Board& boardGame);
	void updateFruitCurrLocation(Board& boardGame);
	bool isValidFruitLocation(Coordinate& fruitCoord, Board& boardGame);
	void randDirection(Coordinate& nextCoord);
	void createNewFruit(Coordinate& currCoordFruit, Coordinate& nextCoordFruit, Board& boardGame);
	void FruitLeaveTheGame(Coordinate& nextCoordFruit, Board& boardGame, const int& mode);
	void function(std::fstream& fileSteps, Board& boardGame, char currLine[], const int& mode);



};
#endif

