#include "Pacman.h"

//--------------------------------------------------------------------------------------------------------------------//
Pacman::Pacman(Coordinate coord, int& score, int& lives)
{
	setLives(lives);
	setDirection(Direction::STAY);
	setSign('@');
	setCurrLocation(coord);
	setStartLocation(coord);
	m_breadCrumbEaten = 0;
	setCoins(score);
}
//--------------------------------------------------------------------------------------------------------------------//
/*
void Pacman::updatePacmanCoordinate(Direction keyFromTheUser, Coordinate& nextCoord)
{
	if (keyFromTheUser == Direction::LEFT)
	{
		nextCoord.setCoordX(nextCoord.getCoordX() - 1);
	}
	else if (keyFromTheUser == Direction::RIGHT)
	{
		nextCoord.setCoordX(nextCoord.getCoordX() + 1);
	}
	else if (keyFromTheUser == Direction::UP)
	{
		nextCoord.setCoordY(nextCoord.getCoordY() - 1);
	}
	else if (keyFromTheUser == Direction::DOWN)
	{
		nextCoord.setCoordY(nextCoord.getCoordY() + 1);
	}
	//If the direction is 'stay', everything remains the same.
}
*/
//--------------------------------------------------------------------------------------------------------------------//
void Pacman::move(Board& boardGame, const int& mode, std::fstream& fileSteps, int i)
{
	Coordinate currCoordPacman, nextCoordPacman;
	currCoordPacman = getCurrLocation();
	nextCoordPacman = coordInCurrDirection();
	crossTheScreen(currCoordPacman, nextCoordPacman, getDirection(), boardGame.getRows(), boardGame.getCols());

	if (isValidMove(nextCoordPacman, boardGame))
	{
		boardGame.setPacman(currCoordPacman, false);
		if (!boardGame.getGhost(currCoordPacman))
			boardGame.setEmpty(currCoordPacman); // default = true

		if (boardGame.getEmpty(nextCoordPacman))
		{
			boardGame.setEmpty(nextCoordPacman, false);
			boardGame.setPacman(nextCoordPacman);
		}
		else if (boardGame.getFood(nextCoordPacman))
		{
			boardGame.setFood(nextCoordPacman, false);
			boardGame.setPacman(nextCoordPacman);
			m_coins++;
			m_breadCrumbEaten++;
		}
		else
			boardGame.setPacman(nextCoordPacman);
		setCurrLocation(nextCoordPacman);

		if (mode != (int)Mode::Silent)
		{
			boardGame.printCell(currCoordPacman, '0');
			boardGame.printCell(nextCoordPacman, '0');
		}
	}
	else
		setDirection(Direction::STAY);

	if (mode == (int)Mode::Save)
		fileSteps << i << ":" << (char)getDirection() << std::endl;


	counterUp();
}

//--------------------------------------------------------------------------------------------------------------------//
const bool Pacman::isValidMove(const Coordinate& nextCoord,const Board& boardGame)
{
	return !boardGame.getWall(nextCoord);
}
//--------------------------------------------------------------------------------------------------------------------//
//This function change the coordinates of pacman when he cross the screen in an invisible tunnel
void Pacman::crossTheScreen(Coordinate& currCoord, Coordinate& nextCoord, const Direction direction, const int& rows, const int& cols)
{
	if (Direction::LEFT == direction)
	{
		if (currCoord.getCoordX() == 0)
			nextCoord.setCoordX(cols - 1); // because '/0' after string
	}
	if (Direction::RIGHT == direction)
	{
		if (currCoord.getCoordX() == (cols - 1))
			nextCoord.setCoordX(0);
	}
	if (Direction::UP == direction)
	{
		if (currCoord.getCoordY() == 0)
			nextCoord.setCoordY(rows - 1);
	}
	if (Direction::DOWN == direction)
	{
		if (currCoord.getCoordY() == (rows - 1))
			nextCoord.setCoordY(0);
	}
}
//--------------------------------------------------------------------------------------------------------------------//