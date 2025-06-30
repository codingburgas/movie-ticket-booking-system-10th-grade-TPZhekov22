#include <iostream>
#include <string>
#include <thread>
#include "../system_static_library/namespaceUtility.h"
#include "accountSignIn.h"
#include "createNewObjects.h"
#include "loadObjectData.h"

Account accountSignIn()
{
	do
	{
		utility::displayTitleGraphic("../assets/titleGraphics/menuGraphics/accountSignInTitleGraphic.txt");

		std::cout << "Welcome to the Movie Ticket Booking System!" << '\n';
		std::cout << "Please log in if you already have an account or create one if not." << '\n';
		std::cout << "Alternately, you can log in as a guest." << '\n';
		std::cout << '\n';
		std::cout << "1: Log in as an existing user" << '\n';
		std::cout << "2: Create a new account" << '\n';
		std::cout << "3: Log in as a guest" << '\n';
		std::cout << "4: Exit to Desktop" << '\n';
		int loginOption;
		std::cin >> loginOption;
		Account account;
		switch (loginOption)
		{
		case 1:
			account = logInAccount();
			utility::clearScreen();
			if (account.getUsername() != "guest" && account.getPassword() != "guest")
			{
				return account;
			}

			break;
		case 2:
			utility::clearScreen();
			createNewAccount();
			utility::clearScreen();

			break;
		case 3:
			std::cout << "Logging in as guest..." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(2));
			utility::clearScreen();
			return {};

			break;
		case 4:
			utility::clearScreen();

			std::cout << "Exiting..." << '\n';
			utility::exit = true;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			return {};

			break;
		default:
			std::cout << "Invalid option" << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::this_thread::sleep_for(std::chrono::seconds(1));
			utility::clearScreen();
			break;
		}
	}
	while (utility::exit != true);
}
