#include <iostream>
#include "../system_static_library/namespaceUtility.h"
#include "cinemaObjects.h"
#include "menus.h"

void cityMenu(City& currentCity)
{
	utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt");
	std::cout << "City: " << currentCity.getCityName() << '\n';
	currentCity.displayCinemas();

	std::cout << "1: Create new cinema" << '\n';
	std::cout << "2: Go back" << '\n';
	int cityMenuScreen;
	do {
		std::cin >> cityMenuScreen;
		if (cityMenuScreen < 1 || cityMenuScreen > 2) {
			std::cout << "Invalid option" << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (cityMenuScreen < 1 || cityMenuScreen > 2);
	if (cityMenuScreen == 1)
	{
		createNewCinema(currentCity);
	}
	else
	{
		utility::clearScreen();
	}
}