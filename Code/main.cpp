#include <iostream>
#include "Menu.h"

void main(int argc, char** argv)
{
	Menu m;
	try {
		m.gameManager(argc, argv);
	}
	catch (const char* strError)
	{
		std::cout << strError;
	}
}