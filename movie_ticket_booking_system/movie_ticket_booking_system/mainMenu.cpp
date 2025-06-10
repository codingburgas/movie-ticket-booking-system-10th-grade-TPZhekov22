#include <iostream>
#include <fstream>
#include <string>
#include "selectPlace.h"
#include "definitions.h"
#include "../system_static_library/namespaceUtility.h"

void mainMenu()
{
	utility::displayTitleGraphic("../assets/titleGraphics/mainMenuTitleGraphic.txt");

	std::cout << "1: Select City" << '\n';
	std::cout << "2: Exit" << '\n';
	int mainMenuScreen;
	do {
		std::cin >> mainMenuScreen;
		if (mainMenuScreen < MIN_MENU_CHOICES || mainMenuScreen > MAIN_MENU_MAX_CHOICES) {
			std::cout << "Invalid option" << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (mainMenuScreen < MIN_MENU_CHOICES || mainMenuScreen > MAIN_MENU_MAX_CHOICES);

	switch (mainMenuScreen)
	{
	case 1:
		utility::clearScreen();
		selectCity();
		break;

	case 2:
		utility::clearScreen();

		std::cout << "Exiting..." << '\n';
		utility::exit = true;
		break;
	}
}
