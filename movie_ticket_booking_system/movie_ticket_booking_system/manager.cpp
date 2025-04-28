#include <iostream>
#include "manager.h"
#include "menus.h"
#include "../system_static_library/namespaceUtility.h"

void sceneManager()
{
	int mainMenuScreen;
	while (utility::exit == false)
	{
		switch (utility::scene.currentScene)
		{
		case utility::scene.Menu:
			utility::clear();

			mainMenu();
			do{
				std::cin >> mainMenuScreen;
				if (mainMenuScreen < 1 && mainMenuScreen > 3) {
					std::cout << "Invalid option" << '\n';
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}while (mainMenuScreen < 1 && mainMenuScreen > 3);

			switch (mainMenuScreen)
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

			
			break;
		case utility::scene.ExitEnum:
			utility::clear();

			std::cout << "Exiting..." << '\n';
			utility::exit = true;
			break;
		}
	}
}