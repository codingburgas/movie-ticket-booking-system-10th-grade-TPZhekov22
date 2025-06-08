#include <iostream>
#include <fstream>
#include <string>
#include "definitions.h"
#include "../system_static_library/namespaceUtility.h"

void cityMenu()
{
	utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt");//Add title graphic later
	std::cout << "1: Select a cinema" << '\n';
	std::cout << "2: Add a City" << '\n';
	std::cout << "2: Back to main menu" << '\n';
	int cityMenuScreen;
	do {
		std::cin >> cityMenuScreen;
		if (cityMenuScreen < MIN_MENU_CHOICES || cityMenuScreen > CITY_MENU_MAX_CHOICES) {
			std::cout << "Invalid option" << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (cityMenuScreen < MIN_MENU_CHOICES || cityMenuScreen > CITY_MENU_MAX_CHOICES);
	switch (cityMenuScreen)
	{
	case 1:
		utility::scene.currentScene = utility::scene.Cinemas;
		break;
	case 2:
		utility::scene.currentScene = utility::scene.Menu;
		break;
	}
}