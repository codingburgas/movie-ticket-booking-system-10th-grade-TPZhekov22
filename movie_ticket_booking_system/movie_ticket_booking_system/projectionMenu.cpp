#include <iostream>
#include "../system_static_library/namespaceUtility.h"
#include "cinemaObjects.h"
#include "definitions.h"
#include "menus.h"
#include <vector>
#include <thread>
#include <chrono>
#include "optionsProjectionMenu.h"

void projectionMenu(MovieProjection& currentMovieProjection, Hall& currentHall, Cinema& currentCinema, City& currentCity)
{
	do
	{
		std::vector<std::vector<int>> selectedSeats;
		selectedSeats.resize(SEAT_PLAN_ROWS);
		do
		{
			utility::displayTitleGraphic("../assets/titleGraphics/menuGraphics/projectionMenuTitleGraphic.txt");
			// Add title graphic later "MOVIE PROJECTION MENU"
			std::cout << "Movie projection: " << currentMovieProjection.getProjectionMovieTitle() << '\n';
			std::cout << "Genre: " << currentMovieProjection.getProjectionMovieGenre() << '\n';
			std::cout << "Release Date: " << currentMovieProjection.getProjectionMovieReleaseDate() << '\n';
			std::cout << "Language: " << currentMovieProjection.getProjectionMovieLanguage() << '\n';
			std::cout << "Projection Time: " << currentMovieProjection.getProjectionTime() << ":00" << '\n';
			std::cout << "---------------------------------------" << '\n';
			currentMovieProjection.displaySeatPlan();
			std::cout << '\n';
			std::cout << "---------------------------------------" << '\n';
			std::cout << "Current selected seats:" << '\n';
			for (size_t row = 0; row < selectedSeats.size(); row++)
			{
				for (size_t col = 0; col < selectedSeats.at(row).size(); col++)
				{
					if (selectedSeats.at(row).at(col) + 1 != 0)
					{
						std::cout << "row: " << row + 1 << " seat number: " << selectedSeats.at(row).at(col) + 1 <<
							'\n';
					}
				}
			}
			std::cout << "1: Select a seat to book" << '\n';
			std::cout << "2: Unselect seat" << '\n';
			std::cout << "3: Purchase ticket" << '\n';
			std::cout << "4: Go back" << '\n';

			int projectionMenuOption;
			std::cin >> projectionMenuOption;

			switch (projectionMenuOption)
			{
			case 1:
				selectSeatToBook(selectedSeats, currentMovieProjection);
				utility::clearScreen();

				break;

			case 2:
				unselectSeatToBook(selectedSeats);
				utility::clearScreen();

				break;
			case 3:
				purchaseTicket(selectedSeats, currentMovieProjection, currentHall, currentCinema, currentCity);
				for (auto& row : selectedSeats)
				{
					row.clear();
				}

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
				std::this_thread::sleep_for(std::chrono::milliseconds(650));
				utility::clearScreen();
				break;
			}
		}
		while (utility::exit == false);
	}
	while (utility::exit == false);
}