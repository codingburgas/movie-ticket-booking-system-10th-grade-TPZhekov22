#include "menus.h"
#include "createNewObjects.h"
#include "loadObjectData.h"
#include "cinemaObjects.h"
#include "definitions.h"
#include "../system_static_library/namespaceUtility.h"

void cinemaMenu(Cinema& currentCinema)
{
	do
	{
		utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt"); // Add title graphic later "Cinema Menu"
		std::cout << "Cinema: " << currentCinema.getCinemaName() << '\n';
		std::cout << '\n';
		currentCinema.displayMovies();
		std::cout << "---------------------------------------" << '\n';
		std::cout << "1: Select a hall" << '\n';
		std::cout << "2: Create new hall" << '\n';
		std::cout << "3: Go back" << '\n';
		size_t cinemaMenuOption;
		do {
			std::cin >> cinemaMenuOption;
			if (cinemaMenuOption < MIN_MENU_CHOICES || cinemaMenuOption > CINEMA_MENU_MAX_CHOICES) {
				std::cout << "Invalid option" << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (cinemaMenuOption < MIN_MENU_CHOICES || cinemaMenuOption > CINEMA_MENU_MAX_CHOICES);
		switch (cinemaMenuOption)
		{
		case 1:
			utility::clearScreen();
		//	selectHall();  Add later
			
			break;

		case 2:
			utility::clearScreen();
		//	createNewHalls(currentCinema); Add later

			break;
		case 3:
			utility::clearScreen();

			return;
			break;
		}
	} while (utility::exit == false);
}
