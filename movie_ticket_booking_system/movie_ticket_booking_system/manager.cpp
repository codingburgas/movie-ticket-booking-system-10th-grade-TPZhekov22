#include <iostream>
#include "manager.h"
#include "menus.h"
#include "../system_static_library/namespaceUtility.h"

void sceneManager()
{
	int* mainMenuScreen = nullptr;
	mainMenuScreen = new int;
	while (utility::exit == false)
	{
		switch (utility::scene.currentScene)
		{
		case utility::scene.Menu:
			utility::clear();

			mainMenu();
			while (true) {
				std::cin >> *mainMenuScreen;
				if (*mainMenuScreen >= 1 && *mainMenuScreen <= 3) {
					break;
				}
				else {
					std::cout << "Invalid option" << '\n';
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
			switch (*mainMenuScreen)
			{
			case 1:
				utility::scene.currentScene = utility::scene.View;
				break;
			case 2:
				utility::scene.currentScene = utility::scene.ExitEnum;
				break;
			}
			break;

		case utility::scene.View:
			utility::clear();

			viewMenu();
			break;
		case utility::scene.ExitEnum:
			utility::clear();

			delete mainMenuScreen;
			std::cout << "Exiting..." << '\n';
			utility::exit = true;
			break;
		}
	}
}