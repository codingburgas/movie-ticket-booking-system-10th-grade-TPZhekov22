#include "selectPlace.h"
#include <iostream>
#include <fstream>
#include <string>
#include "createNewObjects.h"
#include "loadObjectData.h"
#include "definitions.h"
#include "../system_static_library/namespaceUtility.h"

void selectCity()
{
	utility::displayTitleGraphic("../assets/titleGraphics/cityMenuTitleGraphic.txt");//Add title graphic later
	std::vector<City> cities = loadCitiesFromFile();

	for (size_t numOfCity = 0; numOfCity < cities.size(); numOfCity++)
	{
		std::cout << numOfCity + 1 << ": " << cities[numOfCity].getCityName() << '\n';
	}
	std::cout << cities.size() + 1 << ": Go back" << '\n';
	size_t cityMenuScreen;
	do {
		std::cin >> cityMenuScreen;
		if (cityMenuScreen < MIN_MENU_CHOICES || cityMenuScreen > cities.size() + 1) {
			std::cout << "Invalid option" << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (cityMenuScreen < MIN_MENU_CHOICES || cityMenuScreen > cities.size() + 1);
	if (cityMenuScreen == cities.size() + 1)
	{
		utility::clearScreen();
		return;
	}
	else
	{
		utility::clearScreen();
		std::cout << "You selected: " << cities[cityMenuScreen - 1].getCityName() << '\n';
		
	}
}