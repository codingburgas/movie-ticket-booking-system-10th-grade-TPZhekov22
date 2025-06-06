#include <iostream>
#include "manager.h"
#include "menus.h"
#include "../system_static_library/namespaceUtility.h"

void sceneManager()
{
	while (utility::exit == false)
	{

		switch (utility::scene.currentScene)
		{
		case utility::scene.Menu:
			utility::clearScreen();
			mainMenu();
			break;

		case utility::scene.Cities:
			utility::clearScreen();
			break;

		case utility::scene.Cinemas:
			utility::clearScreen();
			break;

		case utility::scene.ExitEnum:
			utility::clearScreen();

			std::cout << "Exiting..." << '\n';
			utility::exit = true;
			break;
		}
	}
}