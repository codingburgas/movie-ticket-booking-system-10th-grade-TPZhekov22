#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "selectPlace.h"
#include "createNewObjects.h"
#include "deleteObjects.h"
#include "loadObjectData.h"
#include "menus.h"
#include "../system_static_library/namespaceUtility.h"

void mainMenu(Account& currentAccount)
{
	if (currentAccount.getIsAdmin() == false)
	{
		utility::clearScreen();
		selectCity(currentAccount);
		utility::clearScreen();
		std::cout << "Exiting..." << '\n';
		utility::exit = true;
		return;
	}
	else
	{
		while (utility::exit != true)
		{
			utility::displayTitleGraphic("../assets/titleGraphics/menuGraphics/mainMenuTitleGraphic.txt");

			std::cout << "1: Select City" << '\n';
			std::cout << "2: Add new movie" << '\n';
			std::cout << "3: Remove movie" << '\n';
			std::cout << "4: Display all available movies" << '\n';
			std::cout << "5: Manage admins" << '\n';
			std::cout << "6: Exit to Desktop" << '\n';

			int mainMenuOption;
			std::cin >> mainMenuOption;

			switch (mainMenuOption)
			{
			case 1:
				utility::clearScreen();
				selectCity(currentAccount);
				break;

			case 2:
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				utility::clearScreen();
				addNewMovie();
				utility::clearScreen();

				break;
			case 3:
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				utility::clearScreen();
				removeMovie();
				utility::clearScreen();
				break;
			case 4:
				std::cout << '\n';
				displayAllMoviesInDirectory();
				utility::clearScreen();
				break;
			case 5:
				utility::clearScreen();
				manageAdmins();

				break;
			case 6:
				utility::clearScreen();
				std::cout << "Exiting..." << '\n';
				utility::exit = true;
				break;
			default:
				std::cout << "Invalid option" << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::this_thread::sleep_for(std::chrono::milliseconds(650));
				utility::clearScreen();
				break;
			}
		}
	}
}

void displayAllMoviesInDirectory()
{
	std::string dirPath = "../assets/objectData/movieObjects/";

	for (const auto& entry : std::filesystem::directory_iterator(dirPath))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".bin")
		{
			std::ifstream inFile(entry.path(), std::ios::binary);
			if (!inFile) continue;
			auto movieOpt = Movie::loadFromFile(inFile);
			if (!movieOpt) continue;
			const Movie& movie = *movieOpt;
			auto date = movie.getReleaseDate();
			std::cout << "Title: " << movie.getTitle() << '\n'
				<< "Genre: " << movie.getGenre() << '\n'
				<< "Language: " << movie.getLanguage() << '\n'
				<< "Release Date: " << static_cast<int>(date.year()) << '-'
				<< static_cast<unsigned>(date.month()) << '-'
				<< static_cast<unsigned>(date.day()) << "\n\n";
		}
	}
	std::cout << '\n';
	std::cout << "Enter any key to continue..." << '\n';
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

void manageAdmins()
{
	do
	{
		utility::displayTitleGraphic("../assets/titleGraphics/menuGraphics/manageAdminsMenuTitleGraphic.txt");
		utility::listAvailableAccounts();
		std::cout << "---------------------------------------" << '\n';
		std::cout << "1: Give admin to account" << '\n';
		std::cout << "2: Remove admin from account" << '\n';
		std::cout << "3: Go back" << '\n';
		int adminMenuOption;
		std::cin >> adminMenuOption;
		std::cout << '\n';
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (adminMenuOption)
		{
		case 1:
			{
				std::cout << "Select which account you want to give admin to" << '\n';
				std::string giveAdminUsername;
				std::getline(std::cin, giveAdminUsername);
				if (utility::doesFileNameExists(giveAdminUsername, "../assets/objectData/accountObjects/"))
				{
					auto adminAccountOpt = loadAccountFromFile(giveAdminUsername);
					if (adminAccountOpt && adminAccountOpt->getUsername() != "guest")
					{
						Account adminAccount = *adminAccountOpt;
						adminAccount.setAdmin(true);
						if (saveAccountToFile(adminAccount))
						{
							std::cout << "Account " << giveAdminUsername << " is now an admin." << '\n';
							std::this_thread::sleep_for(std::chrono::seconds(2));
						}
						else
						{
							std::cerr << "Error: Failed to save account changes." << '\n';
							std::this_thread::sleep_for(std::chrono::seconds(3));
						}
					}
					else
					{
						std::cout << "Cannot give admin rights to guest account or account failed to load." << '\n';
						std::this_thread::sleep_for(std::chrono::seconds(4));
					}
				}
				else
				{
					std::cout << "Account not found." << '\n';
					std::this_thread::sleep_for(std::chrono::seconds(4));
				}

				utility::clearScreen();
				return;
				break;
			}
		case 2:
			{
				std::cout << "Select which account you want to remove admin from" << '\n';
				std::string removeAdminUsername;
				std::getline(std::cin, removeAdminUsername);
				if (utility::doesFileNameExists(removeAdminUsername, "../assets/objectData/accountObjects/"))
				{
					auto accountRemoveAdminOpt = loadAccountFromFile(removeAdminUsername);
					if (accountRemoveAdminOpt && accountRemoveAdminOpt->getUsername() != "guest")
					{
						Account removeAdminAccount = *accountRemoveAdminOpt;
						removeAdminAccount.setAdmin(false);
						if (saveAccountToFile(removeAdminAccount))
						{
							std::cout << "Admin has been removed from the account: " << removeAdminUsername << '\n';
							std::this_thread::sleep_for(std::chrono::seconds(2));
						}
						else
						{
							std::cerr << "Error: Failed to save account changes." << '\n';
							std::this_thread::sleep_for(std::chrono::seconds(3));
						}
					}
					else
					{
						std::cout << "Account failed to load." << '\n';
						std::this_thread::sleep_for(std::chrono::seconds(3));
					}
				}
				else
				{
					std::cout << "Account not found." << '\n';
					std::this_thread::sleep_for(std::chrono::seconds(3));
				}

				utility::clearScreen();
				return;
				break;
			}
		case 3:
			utility::clearScreen();
			return;
		default:
			std::cout << "Invalid option" << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::this_thread::sleep_for(std::chrono::seconds(1));
			utility::clearScreen();
			break;
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	while (utility::exit == false);
}
