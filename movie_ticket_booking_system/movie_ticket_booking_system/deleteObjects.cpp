#include "deleteObjects.h"
#include <iostream>
#include "cinemaObjects.h"
#include "createNewObjects.h"
#include "loadObjectData.h"
#include "../system_static_library/namespaceUtility.h"
#include <filesystem>
#include <fstream>
#include <thread>

// Movie projection deletion function
void deleteMovieProjection(Hall& currentHall, Cinema& currentCinema, City& currentCity)
{
	std::cout << '\n';
	std::cout << "Select which movie projection you want to delete from this hall or cancel by typing '12345': ";
	int selectedProjection;
	std::cin >> selectedProjection;
	selectedProjection = selectedProjection - 1; // Adjust for zero-based index

	auto& projections = currentHall.getProjectionPlan();
	if (selectedProjection < 0 || static_cast<size_t>(selectedProjection) >= projections.size()) {
		std::cerr << "Invalid projection index.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return;
	}
	if (selectedProjection == 12345)
	{
		std::cout << "Movie projection deletion cancelled." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return;
	}

	std::cout << "WARNING: THIS ACTION WILL DELETE THE MOVIE PROJECTION '" << projections.at(selectedProjection).getProjectionMovieTitle()
		<< "' FROM THE DATA FILES AND ALL THE TICKETS BOOKED FOR THIS PROJECTION!!!" << '\n';
	std::cout << "ARE YOU ABSOLUTELY CERTAIN YOU WANT TO CONTINUE WITH THIS ACTION?" << '\n';
	std::cout << "Confirm deletion of the movie projection '" << projections.at(selectedProjection).getProjectionMovieTitle() << "'? (y/n): ";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	char confirm;
	std::cin >> confirm;

	if (confirm != 'y' && confirm != 'Y')
	{
		std::cout << "Movie deletion cancelled." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return;
	}

	projections.erase(projections.begin() + selectedProjection);
	std::vector<City> cities = loadCitiesFromFile();
	for (auto& city : cities) {
		if (city.getCityName() == currentCity.getCityName()) {
			for (auto& cinema : city.getCinemasVector()) {
				if (cinema.getCinemaName() == currentCinema.getCinemaName()) {
					for (auto& hall : cinema.getHallsVector()) {
						if (hall.getHallID() == currentHall.getHallID()) {
							hall = currentHall;
						}
					}
				}
			}
		}
	}
	if (saveCitiesToFile(cities)) {
		std::cout << "Movie projection deleted successfully.\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	else {
		std::cerr << "Error: Failed to save changes.\n";
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}


// Movie removal function
void removeMovie()
{
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


	std::string filePath = "../assets/objectData/movieObjects/" + movieTitle + ".bin";
	if (!std::filesystem::exists(filePath))
	{
		std::cout << "Movie file not found." << '\n';
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

	if (confirm != 'y' && confirm != 'Y')
	{
		std::cout << "Movie deletion cancelled." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return;
	}

	std::ifstream inFile(filePath, std::ios::binary);
	auto movieOpt = Movie::loadFromFile(inFile);
	inFile.close();
	if (!movieOpt)
	{
		std::cout << "Failed to load movie file." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return;
	}
	const Movie& movie = *movieOpt;
	if (movie.getTitle() != movieTitle ||
		movie.getGenre() != movieGenre ||
		movie.getLanguage() != movieLanguage ||
		movie.getReleaseDate() != movieReleaseDate)
	{
		std::cout << "Movie details do not match." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return;
	}

	std::filesystem::remove(filePath);
	std::cout << "Movie file deleted." << '\n';

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
		std::cout << "All projections with this movie have been removed." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
	else
	{
		std::cerr << "Error: Movie projection removal failed." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}