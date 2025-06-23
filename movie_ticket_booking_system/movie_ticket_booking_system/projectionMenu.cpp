#include <iostream>
#include "../system_static_library/namespaceUtility.h"
#include "cinemaObjects.h"
#include "definitions.h"
#include "menus.h"
#include <vector>
#include <thread>
#include <chrono>

void projectionMenu(MovieProjection& currentMovieProjection, Hall& currentHall, Cinema& currentCinema,
                    City& currentCity)
{
	do
	{
		std::vector<std::vector<int>> selectedSeats;
		selectedSeats.resize(SEAT_PLAN_ROWS);
		do
		{
			utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt");
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
			//ADD PRICE
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
			int projectionMenuOption;
			std::cout << "1: Select a seat to book" << '\n';
			std::cout << "2: Unselect seat" << '\n';
			std::cout << "3: Purchase ticket" << '\n';
			std::cout << "4: Go back" << '\n';

			do
			{
				std::cin >> projectionMenuOption;
				if (projectionMenuOption < MIN_MENU_CHOICES || projectionMenuOption > PROJECTION_MENU_MAX_CHOICES)
				{
					std::cout << "Invalid option" << '\n';
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
			while (projectionMenuOption < MIN_MENU_CHOICES || projectionMenuOption > HALL_MENU_MAX_CHOICES);

			switch (projectionMenuOption)
			{
			case 1:
				int selectedRow;
				std::cout << "Select row (1-" << SEAT_PLAN_ROWS << ") or to cancel type '1234': ";
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


					std::cout << "Select seat number (1-" << SEAT_PLAN_COLS << ") or to cancel type '1234':  ";
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
						if (utility::vectorLinearSearchRow2D(selectedSeats, selectedRow - 1, selectedCol - 1))
						{
							std::cout << "This seat is already selected." << '\n';
							std::this_thread::sleep_for(std::chrono::seconds(3));
						}
						else if (currentMovieProjection.checkSeatAvailability(selectedRow - 1, selectedCol - 1))
						
						{
							std::cout << "This seat has already been booked and is unavailable." << '\n';
							std::this_thread::sleep_for(std::chrono::seconds(3));
						}
						else
						{
							std::cout << "seat row: " << selectedRow << " seat number: " << selectedCol << '\n';

							std::cout << "Confirm selection of the seat? (y/n): " << '\n';
							char confirm;
							std::cin >> confirm;
							if (confirm == 'y' || confirm == 'Y')
							{
								selectedSeats.at(selectedRow - 1).push_back(selectedCol - 1);
								// These are the true indexes of the vector (from 0)
							}
							else
							{
								std::cout << "Seat selection cancelled." << '\n';
								std::this_thread::sleep_for(std::chrono::seconds(2));
							}
						}
					}
					else
					{
						std::cout << "Seat selection cancelled." << '\n';
						std::this_thread::sleep_for(std::chrono::seconds(2));
					}
				}
				utility::clearScreen();
				break;

			case 2:
				int cancelRow;
				std::cout << "Select row (1-" << SEAT_PLAN_ROWS << ") or to cancel type '1234':  ";
				do
				{
					std::cin >> cancelRow;
					if ((cancelRow < MIN_MENU_CHOICES || cancelRow > SEAT_PLAN_ROWS) && cancelRow != 1234)
					{
						std::cout << "Invalid option" << '\n';
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
				}
				while ((cancelRow < MIN_MENU_CHOICES || cancelRow > SEAT_PLAN_ROWS) && cancelRow != 1234);

				if (cancelRow != 1234)
				{
					int cancelCol;
					std::cout << "seat row: " << cancelRow << " seat number: ?" << '\n';


					std::cout << "Select seat number (1-" << SEAT_PLAN_COLS << ") or to cancel type '1234':  ";
					do
					{
						std::cin >> cancelCol;
						if ((cancelCol < MIN_MENU_CHOICES || cancelCol > SEAT_PLAN_ROWS) && cancelCol != 1234)
						{
							std::cout << "Invalid option" << '\n';
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
					}
					while ((cancelCol < MIN_MENU_CHOICES || cancelCol > SEAT_PLAN_ROWS) && cancelCol != 1234);
					if (cancelCol != 1234)
					{
						utility::removeFrom2DVectorRow(selectedSeats, cancelRow - 1, cancelCol - 1);
					}
					else
					{
						std::cout << "Canceled seat unselection." << '\n';
						std::this_thread::sleep_for(std::chrono::seconds(2));
					}
				}
				utility::clearScreen();

				break;
			case 3:
				if (selectedSeats.empty() || utility::is2DVectorEmpty(selectedSeats))
				{
					std::cout << "No seats selected." << '\n';
					std::cout << "Going back to the projection menu..." << '\n';
					std::this_thread::sleep_for(std::chrono::seconds(3));
				}
				else
				{
					double sum = 0;


					int rowIndex = 0;
					for (const auto& row : selectedSeats)
					{
						if (!row.empty())
						{
							for (const auto& seat : row)
							{
								if (seat + 1 != 0)
								{
									if (rowIndex < PLATINUM_SEAT_ROW_LIMIT)
									{
										sum += PLATINUM_SEAT_PRICE;
									}
									else if (rowIndex < GOLD_SEAT_ROW_LIMIT)
									{
										sum += GOLD_SEAT_PRICE;
									}
									else
									{
										sum += SILVER_SEAT_PRICE;
									}
								}
							}
						}
						++rowIndex;
					}

					std::cout << "Current selected seats:" << '\n';
					for (size_t row = 0; row < selectedSeats.size(); row++)
					{
						for (size_t col = 0; col < selectedSeats.at(row).size(); col++)
						{
							if (selectedSeats.at(row).at(col) + 1 != 0)
							{
								std::cout << "row: " << row + 1 << " seat number: " << selectedSeats.at(row).at(col) + 1
									<< " - ";
								if (row < PLATINUM_SEAT_ROW_LIMIT)
								{
									std::cout << "Platinum seat: " << PLATINUM_SEAT_PRICE << " BGN" << '\n';
								}
								else if (row < GOLD_SEAT_ROW_LIMIT)
								{
									std::cout << "Gold seat: " << GOLD_SEAT_PRICE << " BGN" << '\n';
								}
								else
								{
									std::cout << "Silver seat: " << SILVER_SEAT_PRICE << " BGN" << '\n';
								}
							}
						}
					}
					std::cout << '\n';
					std::cout << "Total price: " << sum << " BGN" << '\n';
				}
				std::this_thread::sleep_for(std::chrono::seconds(7)); //DO THIS NOW (STILL NOT FINISHED) <----
				utility::clearScreen();

				break;
			case 4:
				utility::clearScreen();
				return;

				break;
			}
		}
		while (utility::exit == false);
	}
	while (utility::exit == false);
}
