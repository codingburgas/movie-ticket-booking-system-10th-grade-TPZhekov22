#include "selectPlace.h"
#include <iostream>
#include <fstream>
#include <string>
#include "createNewObjects.h"
#include "loadObjectData.h"
#include "definitions.h"
#include "menus.h"
#include "../system_static_library/namespaceUtility.h"

void selectCity()
{
	std::vector<City> cities = loadCitiesFromFile();
	do
	{
	utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt");//Add title graphic later
	

	for (size_t numOfCity = 0; numOfCity < cities.size(); numOfCity++)
	{
		std::cout << numOfCity + 1 << ": " << cities[numOfCity].getCityName() << '\n';
	}
	std::cout << cities.size() + 1 << ": Go back" << '\n';
	size_t selectedCityOption;
	do {
		std::cin >> selectedCityOption;
		if (selectedCityOption < MIN_MENU_CHOICES || selectedCityOption > cities.size() + 1) {
			std::cout << "Invalid option" << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (selectedCityOption < MIN_MENU_CHOICES || selectedCityOption > cities.size() + 1);
	if (selectedCityOption == cities.size() + 1)
	{
		utility::clearScreen();
		return;
	}
	else
	{
		utility::clearScreen();
		cityMenu(cities.at(selectedCityOption - 1));

	}
	} while (utility::exit == false);
	saveCitiesToFile(cities);
}

void selectCinema(City& currentCity)
{
	do
	{
	utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt"); // Add title graphic later "SELECT A CINEMA"
	std::cout << "City: " << currentCity.getCityName() << '\n';
	std::cout << '\n';
	currentCity.displayCinemas();
	std::cout << currentCity.numberOfCinemas() + 1 << ": Go back" << '\n';
	std::cout << "---------------------------------------" << '\n';

	size_t selectedCinemaOption;
	do {
		std::cin >> selectedCinemaOption;
		if (selectedCinemaOption < MIN_MENU_CHOICES || selectedCinemaOption > currentCity.numberOfCinemas() + 1) {
			std::cout << "Invalid option" << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (selectedCinemaOption < MIN_MENU_CHOICES || selectedCinemaOption > currentCity.numberOfCinemas() + 1);
		if (selectedCinemaOption == currentCity.numberOfCinemas() + 1)
		{
			utility::clearScreen();
			return;
		}
		else
		{
			utility::clearScreen();
			cinemaMenu(currentCity.getCinemasVector().at(selectedCinemaOption - 1), currentCity);
		}
	} while (utility::exit == false);
}

void selectHall(Cinema& currentCinema, City& currentCity)
{
	do
	{
		utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt"); // Add title graphic later "SELECT A HALL"
		std::cout << "Cinema: " << currentCinema.getCinemaName() << '\n';
		std::cout << '\n';
		currentCinema.displayMovies();
		std::cout << currentCinema.numberOfHalls() + 1 << ": Go back" << '\n';
		std::cout << "---------------------------------------" << '\n';
		size_t selectedHallOption;
		do {
			std::cin >> selectedHallOption;
			if (selectedHallOption < MIN_MENU_CHOICES || selectedHallOption > currentCinema.numberOfHalls() + 1) {
				std::cout << "Invalid option" << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (selectedHallOption < MIN_MENU_CHOICES || selectedHallOption > currentCinema.numberOfHalls() + 1);
		if (selectedHallOption == currentCinema.numberOfHalls() + 1)
		{
			utility::clearScreen();
			return;
		}
		else
		{
			utility::clearScreen();
			hallMenu(currentCinema.getHallsVector().at(selectedHallOption - 1), currentCinema, currentCity);
		}
	} while (utility::exit == false);
}

void selectMovieProjection(Hall& currentHall, Cinema& currentCinema, City& currentCity)
{
	do
	{
		utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt"); // Add title graphic later "SELECT A MOVIE PROJECTION"
		std::cout << "Hall ID: " << currentHall.getHallID() << '\n';
		std::cout << '\n';
		currentHall.displayProjectionCalendar();
		std::cout << currentHall.numberOfProjections() + 1 << ": Go back" << '\n';
		std::cout << "---------------------------------------" << '\n';
		size_t selectedProjectionOption;
		do {
			std::cin >> selectedProjectionOption;
			if (selectedProjectionOption < MIN_MENU_CHOICES || selectedProjectionOption > currentHall.numberOfProjections() + 1) {
				std::cout << "Invalid option" << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (selectedProjectionOption < MIN_MENU_CHOICES || selectedProjectionOption > currentHall.numberOfProjections() + 1);
		if (selectedProjectionOption == currentHall.numberOfProjections() + 1)
		{
			utility::clearScreen();
			return;
		}
		else
		{
			utility::clearScreen();
			//projectionMenu(currentHall.getProjectionPlan().at(selectedProjectionOption - 1), currentHall, currentCinema, currentCity); // <---- DO THIS NOW
		}
	} while (utility::exit == false);
}