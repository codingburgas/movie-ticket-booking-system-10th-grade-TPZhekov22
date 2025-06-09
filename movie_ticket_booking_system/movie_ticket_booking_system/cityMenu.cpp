#include <iostream>
#include <fstream>
#include <string>
#include "createNewObjects.h"
#include "loadObjectData.h"
#include "definitions.h"
#include "../system_static_library/namespaceUtility.h"

void cityMenu()
{
	utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt");//Add title graphic later
	std::cout << "1: Display Cities" << '\n';
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
		
		break;
	case 2:
		return;

		break;
	}
}