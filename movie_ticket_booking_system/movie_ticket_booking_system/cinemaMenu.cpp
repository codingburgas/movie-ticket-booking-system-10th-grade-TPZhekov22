#include <iostream>
#include <thread>
#include "menus.h"
#include "createNewObjects.h"
#include "cinemaObjects.h"
#include "selectPlace.h"
#include "../system_static_library/namespaceUtility.h"

void cinemaMenu(Cinema& currentCinema, City& currentCity)
{
	do
	{
		utility::displayTitleGraphic("../assets/titleGraphics/menuGraphics/cinemaMenuTitleGraphic.txt");
		// Add title graphic later "Cinema Menu"
		std::cout << "Cinema: " << currentCinema.getCinemaName() << '\n';
		std::cout << '\n';
		currentCinema.displayMovies();
		std::cout << "---------------------------------------" << '\n';
		std::cout << "1: Select a hall" << '\n';
		std::cout << "2: Create new hall" << '\n';
		std::cout << "3: Delete hall" << '\n'; //Add later, when done with menus
		std::cout << "4: Go back" << '\n';

		size_t cinemaMenuOption;
		std::cin >> cinemaMenuOption;

		switch (cinemaMenuOption)
		{
		case 1:
			utility::clearScreen();
			selectHall(currentCinema, currentCity);

			break;

		case 2:
			utility::clearScreen();
			createNewHall(currentCinema, currentCity);
			utility::clearScreen();

			break;
		case 3:
			utility::clearScreen();
			std::cout << "This feature is not implemented yet." << '\n'; //Add later
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