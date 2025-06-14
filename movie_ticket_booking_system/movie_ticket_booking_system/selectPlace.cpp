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

void selectCinema(const City& currentCity)
{
	do
	{
	utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt"); // Add title graphic later "SELECT A CINEMA"
	std::cout << "City: " << currentCity.getCityName() << '\n';
	currentCity.displayCinemas();
	std::cout << currentCity.numberOfCinemas() + 1 << ": Go back" << '\n';
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
			// cinemaMenu function
			utility::clearScreen();
		}
	} while (utility::exit == false);
}