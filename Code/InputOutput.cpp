#include "InputOutput.h"
//--------------------------------------------------------------------------------------------------------------------//
void InputOutput::printGameOver()
{
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY);
	std::cout << "#################" << std::endl;
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY+1);
	std::cout << "#   GAME OVER   #" << std::endl;
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY+2);
	std::cout << "#################" << std::endl;
	Sleep(2000);
	system("cls");
}
//--------------------------------------------------------------------------------------------------------------------//
void InputOutput::printWin()
{
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY);
	std::cout << "#################" << std::endl;
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY + 1);
	std::cout << "#   YOU WIN!!   #" << std::endl;
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY + 2);
	std::cout << "#################" << std::endl;
	Sleep(2000);
	system("cls");


}
//--------------------------------------------------------------------------------------------------------------------//

void InputOutput::printWinInAllScreens()
{
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY);
	std::cout << "################################" << std::endl;
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY + 1);
	std::cout << "#          GOOD JOB!           #" << std::endl;
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY + 2);
	std::cout << "#   YOU WIN ALL THE SCREENS!   #" << std::endl;
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY + 3);
	std::cout << "################################" << std::endl;
	Sleep(3000);
	system("cls");
}

//--------------------------------------------------------------------------------------------------------------------//
void InputOutput::printWelcome()
{
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY);
	std::cout << "***********************************" << std::endl;
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY + 1);
	std::cout << "*     WELCOME TO PACMAN GAME!!    *" << std::endl;
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY + 2);
	std::cout << "***********************************" << std::endl;
	Sleep(2000);
	system("cls");
}
//--------------------------------------------------------------------------------------------------------------------//
void InputOutput::printMenu(bool color) 
{
	setTextColor(Color::WHITE);
	std::cout << "***************** Please choose one of the options: *****************" << std::endl;
	std::cout << "(1) Start a new game" << std::endl;
	std::cout << "(2) start a new game with custom selection screen" << std::endl;
	std::cout << "(7) Color mode: " << ((color) ? "On" : "Off") << std::endl;
	std::cout << "(8) Present instructions and keys" << std::endl;
	std::cout << "(9) EXIT" << std::endl << std::endl;
}
//--------------------------------------------------------------------------------------------------------------------//

void InputOutput::printInstructionsAndKeys()
{
	std::cout << "************************* Welcome to pacman *************************" << std::endl;
	std::cout << "In this game you are the pacman." << std::endl;
	std::cout << "You need to eat all the breadcrumbs if you want to win" << std::endl;
	std::cout << "but beware of the ghosts that run after you!" << std::endl;
	std::cout << "You have 3 lives, if the ghosts catch you, you are dead and lose one live." << std::endl;
	std::cout << "If you lose all the 3 lives, the game is over." << std::endl;
	std::cout << "enjoy :)" << std::endl << std::endl;

	std::cout << "Keys for the game:" << std::endl;
	std::cout << "Left - a or A" << std::endl;
	std::cout << "Right - d or D" << std::endl;
	std::cout << "Up - w or W" << std::endl;
	std::cout << "Down - x or X" << std::endl;
	std::cout << "Stay - s or S" << std::endl << std::endl;

	std::cout << "press the ESC key to pause the game." << std::endl;
	std::cout << "When the game is at pause state, press ESC to continue the game." << std::endl;
	std::cout << "**********************************************************************" << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------//
void InputOutput::printGoodBye() 
{
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY);
	std::cout << "#################" << std::endl;
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY+1);
	std::cout << "#    Goodbye    #" << std::endl;
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY+2);
	std::cout << "#################" << std::endl;
}
//--------------------------------------------------------------------------------------------------------------------//

void InputOutput::printReady()
{
	gotoxy((int)CenterScreen::centerX, (int)CenterScreen::centerY);
	std::cout << "R E A D Y ?" << std::endl;
	Sleep(1000);
	system("cls");
}
//--------------------------------------------------------------------------------------------------------------------//

void InputOutput::printChar(Coordinate coord, char sign, bool color)
{
	gotoxy(coord.getCoordX(), coord.getCoordY());

	if (sign == ' ')
	{
		if (color)
			setTextColor(Color::WHITE);
		std::cout << sign;
	}
	else if (sign == '$')
	{
		if (color)
			setTextColor(Color::RED);
		std::cout << sign;
	}
	else if (sign == '@')
	{
		if (color)
			setTextColor(Color::YELLOW);
		std::cout <<sign;
	}
	else if (sign == '.')
	{
		if (color)
			setTextColor(Color::WHITE);
		std::cout << sign;
	}
	else if (sign == '#')
	{
		if (color)
			setTextColor(Color::BLUEWALLS);
		std::cout << sign;
	}
	else if (sign - '0' >= 5 && sign - '0' <= 9)
	{
		if (color)
			setTextColor(Color::MAGENTA);
		std::cout << sign;
	}

	gotoxy(coord.getCoordX(), coord.getCoordY());
}
//--------------------------------------------------------------------------------------------------------------------//

void InputOutput::printGhostLevel()
{
	system("cls");
	std::cout << "***************** choose game difficulty: *****************" << std::endl;
	std::cout << " 1. Best ghost" << std::endl;
	std::cout << " 2. Good ghost" << std::endl;
	std::cout << " 3. Novice ghost" << std::endl;
}
//--------------------------------------------------------------------------------------------------------------------//

void InputOutput::printChooseFiles(std::vector<std::string> boardFileNames)
{
	int size = boardFileNames.size();
	for (int i = 0; i < size; i++)
		std::cout << "(" << i + 1 << ") " << boardFileNames[i] << std::endl;
}
//--------------------------------------------------------------------------------------------------------------------//
