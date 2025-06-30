#include <iostream>
#include <thread>
#include "../system_static_library/namespaceUtility.h"
#include "cinemaObjects.h"
#include "createNewObjects.h"
#include "menus.h"
#include "selectPlace.h"
#include "deleteObjects.h"

void cityMenu(Account& currentAccount, City& currentCity)
{
	do
	{
		utility::displayTitleGraphic("../assets/titleGraphics/menuGraphics/cityMenuTitleGraphic.txt");
		std::cout << "City: " << currentCity.getCityName() << '\n';
		std::cout << '\n';
		currentCity.displayCinemas();
		std::cout << "---------------------------------------" << '\n';
		std::cout << "1: Select a cinema" << '\n';
		std::cout << "2: Create new cinema" << '\n';
		std::cout << "3: Delete cinema" << '\n';
		std::cout << "4: Go back" << '\n';

		int selectedCinemaOption;
		std::cin >> selectedCinemaOption;

		switch (selectedCinemaOption)
		{
		case 1:
			utility::clearScreen();

			selectCinema(currentAccount, currentCity);
			break;

		case 2:
			utility::clearScreen();
			createNewCinema(currentCity);
			utility::clearScreen();

			break;
		case 3:
			deleteCinema(currentCity);
			utility::clearScreen();

			break;
		case 4:
			utility::clearScreen();
			return;

			break;
		default:
			std::cout << "Invalid option" << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::this_thread::sleep_for(std::chrono::seconds(1));
			utility::clearScreen();
			break;
		}
	}
	while (utility::exit == false);
}
