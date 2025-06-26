#include <iostream>
#include <thread>
#include "menus.h"
#include "createNewObjects.h"
#include "cinemaObjects.h"
#include "selectPlace.h"
#include "../system_static_library/namespaceUtility.h"

void hallMenu(Hall& currentHall, Cinema& currentCinema, City& currentCity)
{
	do
	{
		utility::displayTitleGraphic("../assets/titleGraphics/menuGraphics/hallMenuTitleGraphic.txt");
		// Add title graphic later "Hall Menu"
		std::cout << "Hall ID: " << currentHall.getHallID() << '\n';
		currentHall.displayProjectionCalendar();
		std::cout << "---------------------------------------" << '\n';
		std::cout << "1: Select a movie projection" << '\n';
		std::cout << "2: Add new movie projection" << '\n';
		std::cout << "3: Delete movie projection" << '\n'; //Add later, when done with menus
		std::cout << "4: Go back" << '\n';

		size_t hallMenuOption;
		std::cin >> hallMenuOption;

		switch (hallMenuOption)
		{
		case 1:
			utility::clearScreen();
			selectMovieProjection(currentHall, currentCinema, currentCity);
			break;
		case 2:
			utility::clearScreen();
			createNewMovieProjection(currentHall, currentCinema, currentCity);
			utility::clearScreen();

			break;
		case 3:
			utility::clearScreen();
		// deleteMovieProjection(currentHall, currentCinema, currentCity); // Add later
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