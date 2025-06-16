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
		cityMenu(cities[selectedCityOption - 1]);

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
			cinemaMenu(currentCity.getCinemasVector()[selectedCinemaOption - 1], currentCity);
		}
	} while (utility::exit == false);
}

void selectHall(Cinema& currentCinema)
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
			//hallMenu   <---- DOING THIS RN
		}
	} while (utility::exit == false);
}