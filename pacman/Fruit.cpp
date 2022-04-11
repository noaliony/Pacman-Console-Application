#include "Fruit.h"

Fruit::Fruit()
{
	setAppearance(false);
	m_amountStepWithoutFruit = 5 + rand() % 3;
}
//--------------------------------------------------------------------------------------------------------------------//
void Fruit::move(Board& boardGame, const int& mode, std::fstream& fileSteps, int i) // todo!!!! !! !!
{
	Coordinate currCoordFruit, nextCoordFruit;
	currCoordFruit = nextCoordFruit = getCurrLocation();
	if (mode == (int)Mode::Save || mode == (int)Mode::Regular)
	{
		if (!m_fruitAppear)
		{
			if (getCounterMove() == m_amountStepWithoutFruit)
			{
				createNewFruit(currCoordFruit, nextCoordFruit, boardGame);
				if (mode == (int)Mode::Save)
				{
					fileSteps << i << ":" << (char)getDirection() << " ";
					fileSteps << getCurrLocation().getCoordX() << " ";
					fileSteps << getCurrLocation().getCoordY() << " ";
					fileSteps << getValDigit() << std::endl;
				}
				if (mode != (int)Mode::Silent)
				{
					boardGame.printCell(currCoordFruit, '0');
					boardGame.printCell(nextCoordFruit, getSign());
				}
			}
		}
		else
		{
			if (getCounterMove() < m_fruitLifeTime)
			{
				//int yes = currCoordFruit.getCoordX(), no = currCoordFruit.getCoordY();
				randDirection(nextCoordFruit);

				while (!isValidMove(nextCoordFruit, boardGame))
				{
					nextCoordFruit = currCoordFruit;
					randDirection(nextCoordFruit);
				}
				updateFruitMove(currCoordFruit, nextCoordFruit, boardGame);
				setCurrLocation(nextCoordFruit);

				if (mode == (int)Mode::Save)
					fileSteps << i << ":" << (char)getDirection() << std::endl;

				if (mode != (int)Mode::Silent)
				{
					boardGame.printCell(currCoordFruit, '0');
					boardGame.printCell(nextCoordFruit, getSign());
				}
			}
			else
			{
				fileSteps << "fruit die" << std::endl;
				FruitLeaveTheGame(nextCoordFruit, boardGame, mode);
			}

		}
	}
	else if (m_fruitAppear) 
	{
		nextCoordFruit = coordInCurrDirection();
		updateFruitMove(currCoordFruit, nextCoordFruit, boardGame);
		setCurrLocation(nextCoordFruit);
		if (mode != (int)Mode::Silent)
		{
			boardGame.printCell(currCoordFruit, '0');
			boardGame.printCell(nextCoordFruit, getSign());
		}
	}
	else
		return; //not alive and mode load so we didnt that the fruit will move now
	

	counterUp();
}
//--------------------------------------------------------------------------------------------------------------------//
const bool Fruit::isValidMove(const Coordinate& coord,const Board& boardGame)
{
	if (coord.getCoordX() < 0 || coord.getCoordX() > (boardGame.getCols() - 1) || coord.getCoordY() < 0 || coord.getCoordY() > boardGame.getRows())
		return false;
	return !(boardGame.getWall(coord));

}
//--------------------------------------------------------------------------------------------------------------------//
void Fruit::updateFruitMove(Coordinate& currCoord, Coordinate& nextCoord, Board& boardGame)
{
	boardGame.setFruit(currCoord, false);

	if (!boardGame.getEmpty(currCoord) && !boardGame.getFood(currCoord) && !boardGame.getPacman(currCoord) && !boardGame.getGhost(currCoord))
	{
		boardGame.setEmpty(currCoord); // default = true
	}
	if (boardGame.getEmpty(nextCoord))
	{
		boardGame.setEmpty(nextCoord, false);
		boardGame.setFruit(nextCoord);
	}
	if (boardGame.getFood(nextCoord))
	{
		boardGame.setFruit(nextCoord);
	}
	if (boardGame.getPacman(nextCoord))
	{
		boardGame.setFruit(nextCoord);
	}
	if (boardGame.getGhost(nextCoord))
	{
		boardGame.setFruit(nextCoord);
	}
}
//--------------------------------------------------------------------------------------------------------------------//

void Fruit::updateFruitCurrLocation(Board& boardGame)
{
	Coordinate fruitCoord (rand() % boardGame.getCols()-1, rand() % boardGame.getRows());
	while (!isValidFruitLocation(fruitCoord, boardGame))
	{
		fruitCoord.setCoordX(rand() % boardGame.getCols() -1);
		fruitCoord.setCoordY(rand() % boardGame.getRows());
	}
	setCurrLocation(fruitCoord);
}
//--------------------------------------------------------------------------------------------------------------------//
bool Fruit::isValidFruitLocation(Coordinate& fruitCoord, Board& boardGame)
{
	if (fruitCoord.getCoordX() < 0 || fruitCoord.getCoordX() > (boardGame.getCols() - 1) || fruitCoord.getCoordY() < 0 || fruitCoord.getCoordY() > boardGame.getRows() - 1)
		return false;
	return (!(boardGame.getWall(fruitCoord)) && !(boardGame.getGhost(fruitCoord)) && !(boardGame.getPacman(fruitCoord)));
}

//--------------------------------------------------------------------------------------------------------------------//
// This function is responsible to generate a random direction for each ghost.
void Fruit::randDirection(Coordinate& nextCoord)
{
	const int randDirection = rand() % 4;

	switch (randDirection)
	{
	case (int)randDir::left:
		nextCoord.setCoordX(nextCoord.getCoordX() - 1);
		setDirection(Direction::LEFT);
		break;
	case (int)randDir::right:
		nextCoord.setCoordX(nextCoord.getCoordX() + 1);
		setDirection(Direction::RIGHT);
		break;
	case (int)randDir::up:
		nextCoord.setCoordY(nextCoord.getCoordY() - 1);
		setDirection(Direction::UP);
		break;
	case (int)randDir::down:
		nextCoord.setCoordY(nextCoord.getCoordY() + 1);
		setDirection(Direction::DOWN);

		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------//
void Fruit::createNewFruit(Coordinate& currCoordFruit, Coordinate& nextCoordFruit, Board& boardGame)
{
	updateFruitCurrLocation(boardGame);
	boardGame.setFruit(getCurrLocation());
	currCoordFruit = nextCoordFruit = getCurrLocation();
	setAppearance(true);
	setValDigit(5 + rand() % 5);
	setSign((getValDigit()) + '0');
	setDirection(Direction::STAY);
	m_fruitLifeTime = 20 + rand() % 3;
	counterReset();
}
//--------------------------------------------------------------------------------------------------------------------//
void Fruit::FruitLeaveTheGame(Coordinate& nextCoordFruit, Board& boardGame, const int& mode)
{
	setAppearance(false);
	boardGame.setFruit(nextCoordFruit, false);
	if (mode != (int)Mode::Load)
		m_amountStepWithoutFruit = 5 + rand() % 3;
	boardGame.printCell(nextCoordFruit, '0');
	counterReset();
}

//--------------------------------------------------------------------------------------------------------------------//
void Fruit::function(std::fstream& fileSteps, Board& boardGame, char currLine[], const int& mode)
{
	if (getDirection() == Direction::STAY) //fruit is appear now
	{
		setAppearance(true);
		std::string str;
		getline(fileSteps, str);
		std::stringstream sstream(str);
		int x, y, valDig;
		sstream >> x;
		sstream >> y;
		sstream >> valDig;
		Coordinate coord(x , y);
		setCurrLocation(coord);
		setValDigit(valDig);
		setSign(valDig + '0');
	}
	else if (strcmp(currLine, "fruit die") == 0)//fruit is disappear now
		FruitLeaveTheGame(getCurrLocation(), boardGame, mode);

}

