#include <algorithm>
#include <iostream>
#include "../system_static_library/namespaceUtility.h"
#include "cinemaObjects.h"
#include "definitions.h"
#include <vector>
#include <thread>
#include <chrono>
#include "createNewObjects.h"

void selectSeatToBook(std::vector<std::vector<int>>& selectedSeats, MovieProjection& currentMovieProjection)
{
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
				selectedSeats.at(selectedRow - 1).push_back(selectedCol - 1);
				// These are the true indexes of the vector (from 0)
			}
		}
		else
		{
			std::cout << "Seat selection cancelled." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
	}
}

void unselectSeatToBook(std::vector<std::vector<int>>& selectedSeats)
{
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
}

void purchaseTicket(std::vector<std::vector<int>>& selectedSeats, MovieProjection& currentMovieProjection,
                    Hall& currentHall, Cinema& currentCinema, City& currentCity)
{
	std::cout << '\n';
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
		std::cout << '\n';
		std::cout << "To purchase please input your credit card number: ";
		std::string creditCardNumber;
		do
		{
			std::cin >> creditCardNumber;
			if (creditCardNumber.length() > 16 || creditCardNumber.length() < 15 || !std::ranges::all_of(
				creditCardNumber, isdigit))
			{
				std::cout << "Invalid credit card number. Please input a valid credit card number: ";
				std::cout << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		while (creditCardNumber.length() > 16 || creditCardNumber.length() < 15 || !std::ranges::all_of(
			creditCardNumber, isdigit));
		std::cout << '\n';

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Credit card: " << creditCardNumber << '\n';
		char confirm;
		std::cout << "Confirm purchase? (y/n): ";
		std::cin >> confirm;

		if (confirm == 'y' || confirm == 'Y')
		{
			utility::clearScreen();
			for (int row = 0; row < static_cast<int>(selectedSeats.size()); row++)
			{
				for (int col = 0; col < static_cast<int>(selectedSeats.at(row).size()); col++)
				{
					currentMovieProjection.bookTicket(row, selectedSeats.at(row).at(col));
				}
			}
			saveMovieProjection(currentHall, currentCinema, currentCity, currentMovieProjection);
			utility::displayTitleGraphic("../assets/titleGraphics/menuGraphics/ticketMenuTitleGraphic.txt");
			std::cout << "-------------------------------------------------" << '\n';
			std::cout << "Cinema: " << currentCinema.getCinemaName() << '\n';
			std::cout << "Movie: " << currentMovieProjection.getProjectionMovieTitle() << '\n';
			std::cout << "Hall: " << currentHall.getHallID() << '\n';
			std::cout << "Projection time: " << currentMovieProjection.getProjectionTime() << ":00" << '\n';
			std::cout << "Selected seats:" << '\n';
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
			std::cout << "-------------------------------------------------" << '\n';
			std::cout << '\n';
			std::cout << "Total price: " << sum << " BGN" << '\n';
			std::cout << '\n';
			std::cout << "Tickets purchased successfully!" << '\n';
			std::cout << "Thank you for your purchase!" << '\n';
			std::cout << '\n';
			std::cout << "Enter any key to continue..." << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
		}
		else
		{
			std::cout << "Ticket purchase cancelled." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
	}
}
