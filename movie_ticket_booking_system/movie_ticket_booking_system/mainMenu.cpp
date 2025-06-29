#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "selectPlace.h"
#include "createNewObjects.h"
#include "deleteObjects.h"
#include "menus.h"
#include "../system_static_library/namespaceUtility.h"

void mainMenu()
{
	utility::displayTitleGraphic("../assets/titleGraphics/menuGraphics/mainMenuTitleGraphic.txt");

	std::cout << "1: Select City" << '\n';
	std::cout << "2: Add new movie" << '\n';
	std::cout << "3: Remove movie" << '\n';
	std::cout << "4: Display all available movies" << '\n';
	std::cout << "5: Exit" << '\n';

	int mainMenuOption;
	std::cin >> mainMenuOption;

	switch (mainMenuOption)
	{
	case 1:
		utility::clearScreen();
		selectCity();
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

void displayAllMoviesInDirectory()
{
	namespace fs = std::filesystem;
	std::string dirPath = "../assets/objectData/movieObjects/";

	for (const auto& entry : fs::directory_iterator(dirPath))
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
