#include "deleteObjects.h"
#include <iostream>
#include "cinemaObjects.h"
#include "createNewObjects.h"
#include "loadObjectData.h"
#include "../system_static_library/namespaceUtility.h"
#include <filesystem>
#include <fstream>
#include <thread>

void removeMovie()
{
	using namespace std;
	namespace fs = std::filesystem;

	utility::displayTitleGraphic("../assets/titleGraphics/removeObjectGraphics/removeMovieTitleGraphic.txt");

	std::string movieTitle;
	std::string movieGenre;
	std::string movieLanguage;


	std::cout << "Available movies:\n";
	utility::listAvailableMovies();
	std::cout << '\n';

	std::cout << "Enter the name of the movie: ";
	std::getline(std::cin, movieTitle);

	std::cout << "Enter the genre of the movie: ";
	std::getline(std::cin, movieGenre);

	std::cout << "Enter the language of the movie: ";
	std::getline(std::cin, movieLanguage);

	int year, month, day;
	do
	{
		std::cout << "Enter release date (YYYY MM DD): ";
		std::cin >> year >> month >> day;
		if (!utility::isValidDate(year, month, day))
		{
			std::cout << "Invalid date. Please try again." << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}while (!utility::isValidDate(year, month, day));

	std::chrono::year_month_day movieReleaseDate{
		std::chrono::year{year},
		std::chrono::month{static_cast<unsigned int>(month)},
		std::chrono::day{static_cast<unsigned int>(day)}
	};


	string filePath = "../assets/objectData/movieObjects/" + movieTitle + ".bin";
	if (!fs::exists(filePath))
	{
		cout << "Movie file not found." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return;
	}

	std::cout << "WARNING: THIS ACTION WILL DELETE THE MOVIE '" << movieTitle << "' FROM THE DATA FILES AND ALL THE MOVIE PROJECTIONS WITH THAT MOVIE!!!" << '\n';
	std::cout << "ARE YOU ABSOLUTELY CERTAIN YOU WANT TO CONTINUE WITH THIS ACTION?"  << '\n';
	std::cout << "Confirm deletion of the movie '" << movieTitle <<"'? (y/n): ";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	char confirm;
	std::cin >> confirm;

	ifstream inFile(filePath, ios::binary);
	auto movieOpt = Movie::loadFromFile(inFile);
	inFile.close();
	if (!movieOpt)
	{
		cout << "Failed to load movie file." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return;
	}
	const Movie& movie = *movieOpt;
	if (movie.getTitle() != movieTitle ||
		movie.getGenre() != movieGenre ||
		movie.getLanguage() != movieLanguage ||
		movie.getReleaseDate() != movieReleaseDate)
	{
		cout << "Movie details do not match." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return;
	}

	fs::remove(filePath);
	cout << "Movie file deleted." << '\n';

	std::vector<City> cities = loadCitiesFromFile();
	for (auto& city : cities)
	{
		for (auto& cinema : city.getCinemasVector())
		{
			for (auto& hall : cinema.getHallsVector())
			{
				auto& projections = hall.getProjectionPlan();
				std::erase_if(projections, [&movieTitle](const MovieProjection& projection)
				{
					return projection.getProjectionMovieTitle() == movieTitle;
				});
			}
		}
	}
	if (saveCitiesToFile(cities))
	{
		cout << "All projections with this movie have been removed." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
	else
	{
		std::cerr << "Error: Movie projection removal failed." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}
