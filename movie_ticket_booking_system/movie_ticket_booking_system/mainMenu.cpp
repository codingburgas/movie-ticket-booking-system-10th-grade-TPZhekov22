#include <iostream>
#include <fstream>
#include <string>
#include "../system_static_library/namespaceUtility.h"

void mainMenu()
{
	utility::displayTitleGraphic("../assets/mainMenuTitleGraphic.txt");

	std::cout << "1: Select a city" << '\n';
	std::cout << "2: Exit" << '\n';
	int mainMenuScreen;
	do {
		std::cin >> mainMenuScreen;
		if (mainMenuScreen < 1 || mainMenuScreen > 2) {
			std::cout << "Invalid option" << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (mainMenuScreen < 1 || mainMenuScreen > 2);

	switch (mainMenuScreen)
	{
	case 1:
		utility::scene.currentScene = utility::scene.Cities;
		break;
	case 2:
		utility::scene.currentScene = utility::scene.ExitEnum;
		break;
	}
}
