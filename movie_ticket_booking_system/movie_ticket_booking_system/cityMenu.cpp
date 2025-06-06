#include <iostream>
#include <fstream>
#include <string>
#include "../system_static_library/namespaceUtility.h"

void cityMenu()
{
	utility::displayTitleGraphic("../assets/cityMenuTitleGraphic.txt");//Add title graphic later
	std::cout << "1: Select a cinema" << '\n';
	std::cout << "2: Back to main menu" << '\n';
	int cityMenuScreen;
	do {
		std::cin >> cityMenuScreen;
		if (cityMenuScreen < 1 || cityMenuScreen > 2) {
			std::cout << "Invalid option" << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (cityMenuScreen < 1 || cityMenuScreen > 2);
	switch (cityMenuScreen)
	{
	case 1:
		utility::scene.currentScene = utility::scene.Cinemas;
		break;
	case 2:
		utility::scene.currentScene = utility::scene.Menu;
		break;
	}
}