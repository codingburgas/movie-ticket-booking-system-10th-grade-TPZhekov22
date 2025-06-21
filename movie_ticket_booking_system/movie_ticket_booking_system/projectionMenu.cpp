#include <iostream>
#include "../system_static_library/namespaceUtility.h"
#include "cinemaObjects.h"
#include "createNewObjects.h"
#include "definitions.h"
#include "menus.h"
#include "selectPlace.h"
#include <vector>

#define SEAT_PLAN_ROWS 10
#define SEAT_PLAN_COLS 10

void projectionMenu(MovieProjection& currentMovieProjection, Hall& currentHall, Cinema& currentCinema, City& currentCity)
{
	do
	{
		std::vector<std::vector<int>> selectedSeats;
		selectedSeats.resize(SEAT_PLAN_ROWS);

		utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt"); // Add title graphic later "MOVIE PROJECTION MENU"
		std::cout << "Movie projection: " << currentMovieProjection.getProjectionMovieTitle() << '\n';
		std::cout << "Genre: " << currentMovieProjection.getProjectionMovieGenre() << '\n';
		std::cout << "Release Date: " << currentMovieProjection.getProjectionMovieReleaseDate() << '\n';
		std::cout << "Language: " << currentMovieProjection.getProjectionMovieLanguage() << '\n';
		std::cout << "Projection Time: " << currentMovieProjection.getProjectionTime() << ":00" << '\n';
		std::cout << "To cancel and go back type '1234'" << '\n';
		std::cout << "---------------------------------------" << '\n';
		currentMovieProjection.displaySeatPlan();
		std::cout << '\n';
		std::cout << "---------------------------------------" << '\n';
		//ADD PRICE
		std::cout << "Current selected seats:" << '\n';
		for (size_t row = 0; row < selectedSeats.size(); row++)
		{
			for (size_t col = 0; col < selectedSeats.at(row).size(); col++)
			{
				if (selectedSeats.at(row).at(col) != 0)
				{
					std::cout << "row: " << row + 1 << " seat number: " << selectedSeats.at(row).at(col) << '\n';
				}
			}
		}
		int projectionMenuOption;
		std::cout << "1: Select a seat to book" << '\n';
		std::cout << "2: Cancel selected seat" << '\n';
		std::cout << "3: Purchase ticket" << '\n';
		std::cout << "4: Go back" << '\n';

		std::cin >> projectionMenuOption;
		switch (projectionMenuOption)
		{
		case 1:
			int selectedRow;
			std::cout << "Select row (1-" << SEAT_PLAN_ROWS << "): ";
			do
			{
				std::cin >> selectedRow;
				if ((selectedRow < MIN_MENU_CHOICES || selectedRow > SEAT_PLAN_ROWS) && selectedRow != 1234)
				{
					std::cout << "Invalid option" << '\n';
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
			while ((selectedRow < MIN_MENU_CHOICES || selectedRow > SEAT_PLAN_ROWS) && selectedRow != 1234);

			if (selectedRow != 1234)
			{
				int selectedCol;
				std::cout << "seat row: " << selectedRow << " seat number: ?" << '\n';


			std::cout << "Select seat number (1-" << SEAT_PLAN_COLS << "): ";
			do
			{
				std::cin >> selectedCol;
				if ((selectedCol < MIN_MENU_CHOICES || selectedCol > SEAT_PLAN_ROWS) && selectedCol != 1234)
				{
					std::cout << "Invalid option" << '\n';
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
			while ((selectedCol < MIN_MENU_CHOICES || selectedCol > SEAT_PLAN_ROWS) && selectedCol != 1234);
			if (selectedCol != 1234)
			{
				if (utility::vectorLinearSearch2D(selectedSeats, selectedCol))
				std::cout << "seat row: " << selectedRow << " seat number: " << selectedCol << '\n';

			std::cout << "Confirm selection of the seat? (y/n): " << '\n';
			char confirm;
			std::cin >> confirm;
			if (confirm == 'y' || confirm == 'Y')
			{
				selectedSeatRow.push_back(selectedRow);
				selectedSeatCol.push_back(selectedCol);
			}
			else
			{
				std::cout << "Seat selection cancelled." << '\n';
			}
			}
			}
			else
			{
				std::cout << "Seat selection cancelled." << '\n';
			}

			break;

			case 2:

			break;
		}

	} while (utility::exit == false);
}