#include <iostream>
#include "manager.h"
#include "menus.h"
#include "../system_static_library/namespaceUtility.h"
#include "definitions.h"

void sceneManager()
{
	while (utility::exit == false)
	{
		utility::displayTitleGraphic("../assets/titleGraphics/mainMenuTitleGraphic.txt");

		std::cout << "1: Select City" << '\n';
		std::cout << "2: Exit" << '\n';
		int mainMenuScreen;
		do {
			std::cin >> mainMenuScreen;
			if (mainMenuScreen < MIN_MENU_CHOICES || mainMenuScreen > MAIN_MENU_MAX_CHOICES) {
				std::cout << "Invalid option" << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (mainMenuScreen < MIN_MENU_CHOICES || mainMenuScreen > MAIN_MENU_MAX_CHOICES);

		switch (mainMenuScreen)
		{
		case 1:
			utility::clearScreen();
			cityMenu();
			break;

		case 2:
			utility::clearScreen();

			std::cout << "Exiting..." << '\n';
			utility::exit = true;
			break;
		}
	}
}