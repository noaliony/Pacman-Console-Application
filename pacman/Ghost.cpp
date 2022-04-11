#include "Ghost.h"

//--------------------------------------------------------------------------------------------------------------------//
Ghost::Ghost(Coordinate coord, int ghostLevel)
{
	setSign('$');
	setCurrLocation(coord);
	setDirection(Direction::STAY);
	m_startLocationGhost = getCurrLocation();
	m_bestGhost = m_goodGhost = m_noviceGhost = false;
	if (ghostLevel == 1)
		m_bestGhost = true;
	else if (ghostLevel == 2)
		m_goodGhost = true;
	else if (ghostLevel == 3)
		m_noviceGhost = true;
	counterReset();
}

//--------------------------------------------------------------------------------------------------------------------//
void Ghost::move(Board& boardGame, const int& mode, std::fstream& fileSteps, int i)
{
	Coordinate currCoordGhost, nextCoordGhost;
	currCoordGhost = nextCoordGhost = getCurrLocation();

	if (mode == (int)Mode::Save || mode == (int)Mode::Regular)
	{
		checkPossibleDirections(boardGame);

		if (m_bestGhost)
			moveBest(nextCoordGhost, boardGame);
		else if (m_goodGhost)
			moveGood(nextCoordGhost, boardGame);
		else if (m_noviceGhost)
			moveNovice(nextCoordGhost);
	}
	else
		nextCoordGhost = coordInCurrDirection();

	updateGhostMove(currCoordGhost, nextCoordGhost, boardGame);
	setGhostLocation(nextCoordGhost);

	if (mode == (int)Mode::Save)
		fileSteps << i << ":" << (char)getDirection() << std::endl;

	if (mode != (int)Mode::Silent)
	{
		boardGame.printCell(currCoordGhost, '0');
		boardGame.printCell(nextCoordGhost, '0');
	}
	counterUp();
}
//--------------------------------------------------------------------------------------------------------------------//
void Ghost::moveNovice(Coordinate& nextCoordGhost)
{
	if (getCounterMove() < 20)
	{
		if (getCounterMove() == 0)
			setDirection(validDirections[rand() % validDirections.size()]);
		nextCoordGhost = coordInCurrDirection();

		if (!isDirectionValid(getDirection()))
		{
			setDirection(validDirections[rand() % validDirections.size()]);
			nextCoordGhost = coordInCurrDirection();
		}

		if (getCounterMove() == 19)
			counterReset();
	}
}
//--------------------------------------------------------------------------------------------------------------------//
void Ghost::moveGood(Coordinate& nextCoordGhost, Board& boardGame)
{
	
	if (getCounterMove() < stopBeingSmart)
		moveBest(nextCoordGhost, boardGame);
	else if (getCounterMove() >= stopBeingSmart)
	{
		if (getCounterMove() == stopBeingSmart)
			setDirection(validDirections[rand() % validDirections.size()]);
		nextCoordGhost = coordInCurrDirection();

		if (!isDirectionValid(getDirection()))
		{
			setDirection(validDirections[rand() % validDirections.size()]);
			nextCoordGhost = coordInCurrDirection();
		}

		if (getCounterMove() == stopBeingSmart + 5)
		{
			stopBeingSmart = 18 + rand() % 6;
			counterReset();
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------//
void Ghost::moveBest(Coordinate& nextCoordGhost, Board& boardGame)
{
	if (boardGame.getCoordPacman().getCoordX() < getCurrLocation().getCoordX() && isDirectionValid(Direction::LEFT))
		setDirection(Direction::LEFT);
	else if (boardGame.getCoordPacman().getCoordX() > getCurrLocation().getCoordX() && isDirectionValid(Direction::RIGHT))
		setDirection(Direction::RIGHT);
	else if (boardGame.getCoordPacman().getCoordY() < getCurrLocation().getCoordY() && isDirectionValid(Direction::UP))
		setDirection(Direction::UP);
	else if (boardGame.getCoordPacman().getCoordY() > getCurrLocation().getCoordY() && isDirectionValid(Direction::DOWN))
		setDirection(Direction::DOWN);
	else
		setDirection(validDirections[rand() % validDirections.size()]);

	nextCoordGhost = coordInCurrDirection();
}
//--------------------------------------------------------------------------------------------------------------------//
bool Ghost::isDirectionValid(Direction direction)
{
	return std::find(validDirections.begin(), validDirections.end(), direction) != validDirections.end();
}
//--------------------------------------------------------------------------------------------------------------------//
const bool Ghost::isValidMove(const Coordinate& coord,const Board& boardGame)
{
	if (coord.getCoordX() < 0 || coord.getCoordX() > (boardGame.getCols() - 2) || coord.getCoordY() < 0 || coord.getCoordY() > boardGame.getRows() - 1)
		return false;
	return !(boardGame.getGhost(coord) || boardGame.getWall(coord));
}
//--------------------------------------------------------------------------------------------------------------------//
void Ghost::updateGhostMove(Coordinate& currCoord, Coordinate& nextCoord, Board& boardGame)
{
	boardGame.setGhost(currCoord, false);

	if (!boardGame.getEmpty(currCoord) && !boardGame.getFood(currCoord) && !boardGame.getPacman(currCoord) && !boardGame.getFruit(currCoord))
		boardGame.setEmpty(currCoord); // default = true

	if (boardGame.getEmpty(nextCoord))
	{
		boardGame.setEmpty(nextCoord, false);
		boardGame.setGhost(nextCoord);
	}
	if (boardGame.getFood(nextCoord))
	{
		boardGame.setGhost(nextCoord);
	}
	if (boardGame.getPacman(nextCoord))
	{
		boardGame.setGhost(nextCoord);
	}
	if (boardGame.getFruit(nextCoord))
	{
		boardGame.setGhost(nextCoord);
	}
}
//--------------------------------------------------------------------------------------------------------------------//

void Ghost::checkPossibleDirections(const Board& boardGame)
{
	Coordinate tmpCoord = getCurrLocation();
	validDirections.clear();

	if (isValidMove(Coordinate(tmpCoord.getCoordX() - 1, tmpCoord.getCoordY()), boardGame))
		validDirections.push_back(Direction::LEFT);
	if (isValidMove(Coordinate(tmpCoord.getCoordX() + 1, tmpCoord.getCoordY()), boardGame))
		validDirections.push_back(Direction::RIGHT);
	if (isValidMove(Coordinate(tmpCoord.getCoordX(), tmpCoord.getCoordY() - 1), boardGame))
		validDirections.push_back(Direction::UP);
	if (isValidMove(Coordinate(tmpCoord.getCoordX(), tmpCoord.getCoordY() + 1), boardGame))
		validDirections.push_back(Direction::DOWN);
	if (validDirections.empty())
		validDirections.push_back(Direction::STAY);
}
//--------------------------------------------------------------------------------------------------------------------//

