#include <iostream>
#include <fstream>
#include <string>
#include "definitions.h"
#include "../system_static_library/namespaceUtility.h"

void mainMenu()
{
	utility::displayTitleGraphic("../assets/titleGraphics/mainMenuTitleGraphic.txt");

	std::cout << "1: City Options" << '\n';
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
		utility::scene.currentScene = utility::scene.Cities;
		break;

	case 2:
		utility::scene.currentScene = utility::scene.ExitEnum;
		break;
	}
}
