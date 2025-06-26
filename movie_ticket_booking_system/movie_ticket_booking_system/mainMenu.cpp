#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "selectPlace.h"
#include "createNewObjects.h"
#include "../system_static_library/namespaceUtility.h"

void mainMenu()
{
	utility::displayTitleGraphic("../assets/titleGraphics/menuGraphics/mainMenuTitleGraphic.txt");

	std::cout << "1: Select City" << '\n';
	std::cout << "2: Add new movie" << '\n';
	std::cout << "3: Exit" << '\n';

	int mainMenuOption;
	std::cin >> mainMenuOption;

	switch (mainMenuOption)
	{
	case 1:
		utility::clearScreen();
		selectCity();
		break;

	case 2:
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		utility::clearScreen();
		addNewMovie();
		utility::clearScreen();

		break;
	case 3:
		utility::clearScreen();

		std::cout << "Exiting..." << '\n';
		utility::exit = true;
		break;
	default:
		std::cout << "Invalid option" << '\n';
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::this_thread::sleep_for(std::chrono::milliseconds(650));
		utility::clearScreen();
		break;
	}
}