#include "menus.h"
#include "createNewObjects.h"
#include "loadObjectData.h"
#include "cinemaObjects.h"
#include "definitions.h"
#include "../system_static_library/namespaceUtility.h"

void hallMenu(Hall& currentHall, Cinema& currentCinema, City& currentCity)
{
	do
	{
		utility::displayTitleGraphic("../assets/titleGraphics/hallMenuTitleGraphic.txt"); // Add title graphic later "Hall Menu"
		std::cout << "Hall ID: " << currentHall.getHallID() << '\n';
		std::cout << '\n';
		currentHall.displayProjectionCalendar();
		std::cout << "---------------------------------------" << '\n';
		std::cout << "1: Select a movie projection" << '\n';
		std::cout << "2: Add new movie projection" << '\n';
		std::cout << "3: Delete movie projection" << '\n'; //Add later, when done with menus
		std::cout << "4: Go back" << '\n';
		size_t hallMenuOption;
		do {
			std::cin >> hallMenuOption;
			if (hallMenuOption < MIN_MENU_CHOICES || hallMenuOption > HALL_MENU_MAX_CHOICES) {
				std::cout << "Invalid option" << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (hallMenuOption < MIN_MENU_CHOICES || hallMenuOption > HALL_MENU_MAX_CHOICES);
		switch (hallMenuOption)
		{
		case 1:
			utility::clearScreen();
			// selectMovieProjection(currentHall, currentCinema, currentCity); // Add later
			break;
		case 2:
			utility::clearScreen();
			createNewMovieProjection(currentHall, currentCinema, currentCity);
			break;
		case 3:
			utility::clearScreen();
			// deleteMovieProjection(currentHall, currentCinema, currentCity); // Add later
			break;
		case 4:
			utility::clearScreen();
			return;
			break;
		}
	} while (utility::exit == false);
}