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
	int mainMenuOption;
	do {
		std::cin >> mainMenuOption;
		if (mainMenuOption < MIN_MENU_CHOICES || mainMenuOption > MAIN_MENU_MAX_CHOICES) {
			std::cout << "Invalid option" << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (mainMenuOption < MIN_MENU_CHOICES || mainMenuOption > MAIN_MENU_MAX_CHOICES);

	switch (mainMenuOption)
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
