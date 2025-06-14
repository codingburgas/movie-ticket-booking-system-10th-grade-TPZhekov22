#include <iostream>
#include "../system_static_library/namespaceUtility.h"
#include "cinemaObjects.h"
#include "createNewObjects.h"
#include "definitions.h"
#include "menus.h"
#include "selectPlace.h"

void cityMenu(City& currentCity)
{
	do
	{
		utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt");
		std::cout << "City: " << currentCity.getCityName() << '\n';
		std::cout << '\n';
		currentCity.displayCinemas();
		std::cout << "---------------------------------------" << '\n';
		std::cout << "1: Select a cinema" << '\n';
		std::cout << "2: Create new cinema" << '\n';
		std::cout << "3: Go back" << '\n';
		int selectedCinemaOption;
		do {
			std::cin >> selectedCinemaOption;
			if (selectedCinemaOption < MIN_MENU_CHOICES || selectedCinemaOption > CITY_MENU_MAX_CHOICES) {
				std::cout << "Invalid option" << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (selectedCinemaOption < MIN_MENU_CHOICES || selectedCinemaOption > CITY_MENU_MAX_CHOICES);
		switch (selectedCinemaOption)
		{
		case 1:
			utility::clearScreen();

			selectCinema(currentCity);
			break;

		case 2:
			utility::clearScreen();
			createNewCinema(currentCity);

			break;
		case 3:
			utility::clearScreen();

			return;
			break;
		}
	} while (utility::exit == false);
}
