#include "createNewObjects.h"
#include "cinemaObjects.h"
#include "../system_static_library/namespaceUtility.h"
#include <fstream>
#include <iostream>
#include "loadObjectData.h"
#include <thread>
#include <chrono>
#include <filesystem>

//Cities vector create and save functions
/*void createNewCity()
{
	utility::displayTitleGraphic("../assets/titleGraphics/addObject/createCityTitleGraphic.txt");

	std::string newCityName;
	std::vector<City> cities = loadCitiesFromFile();

	std::cout << "Enter the name of the new city: ";
	std::getline(std::cin, newCityName);

	auto newCity = new City(newCityName);
	cities.push_back(*newCity);
	delete newCity;
	std::cout << "City " << newCityName << " created successfully!" << '\n';
	for (size_t temp = 0; temp < cities.size(); temp++)
	{
		std::cout << "City #" << temp + 1 << ": " << cities[temp].getCityName() << '\n';
	}
	saveCitiesToFile(cities);
	std::this_thread::sleep_for(std::chrono::seconds(3));
}*/

bool saveCitiesToFile(const std::vector<City>& cities)
{
	std::string fullPath = "../assets/objectData/cityObjects/cities.bin";
	std::ofstream outFile(fullPath, std::ios::binary);
	if (!outFile)
	{
		std::cerr << "Error: Unable to open file for writing at " << fullPath << '\n';
		return false;
	}

	size_t numCities = cities.size();
	outFile.write(reinterpret_cast<const char*>(&numCities), sizeof(numCities));
	if (!outFile)
	{
		std::cerr << "Error: Failed to write city count." << '\n';
		outFile.close();
		return false;
	}

	for (const auto& city : cities)
	{
		if (!city.saveToFile(outFile))
		{
			std::cerr << "Error: Failed to save city to file." << '\n';
			outFile.close();
			return false;
		}
	}

	outFile.close();
	return true;
}

//Cinema create and save function
void createNewCinema(City& currentCity)
{
	utility::displayTitleGraphic("../assets/titleGraphics/createObjectGraphics/createCinemaTitleGraphic.txt");
	std::string newCinemaName;
	std::cout << "Enter the name of the cinema: ";
	std::cin.ignore();
	std::getline(std::cin, newCinemaName);

	Cinema newCinema(newCinemaName);

	std::cout << "Name: " << newCinema.getCinemaName() << '\n';
	std::cout << "Confirm creation of the cinema? (y/n): " << '\n';
	char confirm;
	std::cin >> confirm;
	utility::clearScreen();
	if (confirm == 'y' || confirm == 'Y')
	{
		currentCity.addCinema(newCinema);

		std::vector<City> cities = loadCitiesFromFile();

		for (auto& city : cities)
		{
			if (city.getCityName() == currentCity.getCityName())
			{
				city = currentCity;
				break;
			}
		}

		saveCitiesToFile(cities);

		if (saveCitiesToFile(cities))
		{
			std::cout << "Cinema created and saved successfully!" << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
		else
		{
			std::cerr << "Error: Cinema was created but not saved to file." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
	}
	else
	{
		std::cout << "Cinema creation cancelled." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

// Hall create and save function
void createNewHall(Cinema& currentCinema, City& currentCity)
{
	utility::displayTitleGraphic("../assets/titleGraphics/createObjectGraphics/createHallTitleGraphic.txt");
	Hall newHall(static_cast<int>(currentCinema.numberOfHalls()) + 1);
	std::cout << "New hall with ID " << newHall.getHallID() << '\n';
	std::cout << "Confirm creation of the hall? (y/n): ";
	char confirm;
	std::cin >> confirm;
	if (confirm == 'y' || confirm == 'Y')
	{
		currentCinema.addHall(newHall);

		for (auto& cinema : currentCity.getCinemasVector())
		{
			if (cinema.getCinemaName() == currentCinema.getCinemaName())
			{
				cinema = currentCinema;
				break;
			}
		}

		std::vector<City> cities = loadCitiesFromFile();

		for (auto& city : cities)
		{
			if (city.getCityName() == currentCity.getCityName())
			{
				city = currentCity;
				break;
			}
		}

		if (saveCitiesToFile(cities))
		{
			std::cout << "Hall created and saved successfully!" << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
		else
		{
			std::cerr << "Error: Hall was created but not saved to file." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(4));
		}
	}
	else
	{
		std::cout << "Hall creation cancelled." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

// Movie Projection create and save functions
void saveMovieProjection(Hall& currentHall, Cinema& currentCinema, City& currentCity,
                         MovieProjection& updatedProjection)
{
	for (auto& projection : currentHall.getProjectionPlan())
	{
		if (projection.getProjectionTime() == updatedProjection.getProjectionTime())
		{
			projection = updatedProjection;
			break;
		}
	}

	for (auto& hall : currentCinema.getHallsVector())
	{
		if (hall.getHallID() == currentHall.getHallID())
		{
			hall = currentHall;
			break;
		}
	}

	for (auto& cinema : currentCity.getCinemasVector())
	{
		if (cinema.getCinemaName() == currentCinema.getCinemaName())
		{
			cinema = currentCinema;
			break;
		}
	}

	std::vector<City> cities = loadCitiesFromFile();

	for (auto& city : cities)
	{
		if (city.getCityName() == currentCity.getCityName())
		{
			city = currentCity;
			break;
		}
	}

	if (!saveCitiesToFile(cities))
	{
		std::cerr << "Error: Movie projection changes were not saved to file." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(4));
	}
}


void createNewMovieProjection(Hall& currentHall, Cinema& currentCinema, City& currentCity)
{
	utility::displayTitleGraphic("../assets/titleGraphics/createObjectGraphics/createMovieProjectionTitleGraphic.txt");
	std::string movieName;

	std::cout << "Available movies:\n";
	utility::listAvailableMovies();
	std::cout << '\n';
	std::cout << "Enter the name of the movie you want to make a projection for or cancel by typing 'CANCEL MOVIE' : ";

	do
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, movieName);
		if (movieName == "CANCEL MOVIE")
		{
			std::cout << "Movie projection creation cancelled." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(3));
			return;
		}
		if (movieName.empty() || !utility::fileExists("../assets/objectData/movieObjects/" + movieName + ".bin"))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Error: Movie name is empty or it does not exist." << '\n';
			std::cout << "Please enter a valid movie name or type 'CANCEL MOVIE' to cancel: ";
		}
	}
	while (!utility::fileExists("../assets/objectData/movieObjects/" + movieName + ".bin"));

	int startingTime;
	std::cout << "Enter the starting time of the movie projection (0-23): ";
	std::cin.clear();
	do
	{
		std::cin >> startingTime;
		if (std::cin.fail() || startingTime < 0 || startingTime > 23)
		{
			std::cerr << "Error: Invalid input. Please enter a valid starting time (0-23): ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	while (std::cin.fail() || startingTime < 0 || startingTime > 23);

	for (const auto& projection : currentHall.getProjectionPlan())
	{
		if (projection.getProjectionTime() == startingTime)
		{
			std::cerr << "Error: A movie projection already exists at this starting time in the hall." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(3));
			return;
		}
	}

	Movie newMovie = loadMoviesFromFile(movieName);
	MovieProjection newProjection(newMovie, startingTime);
	std::cout << "New Movie Projection Created in hall " << currentHall.getHallID() << ": " << '\n';
	std::cout << "Movie Name: " << newProjection.getProjectionMovieTitle() << '\n';
	std::cout << "Starting Time: " << newProjection.getProjectionTime() << ":00" << '\n';
	std::cout << "Confirm creation of the movie projection? (y/n): ";
	char confirm;
	std::cin >> confirm;
	if (confirm == 'y' || confirm == 'Y')
	{
		currentHall.addProjection(newProjection);
		saveMovieProjection(currentHall, currentCinema, currentCity, newProjection);
	}
	else
	{
		std::cout << "Movie projection creation cancelled." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}

//Movie create and save function
void addNewMovie()
{
	utility::displayTitleGraphic("../assets/titleGraphics/createObjectGraphics/addMovieTitleGraphic.txt");

	std::string movieTitle;
	std::string movieGenre;
	std::string movieLanguage;

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
	}
	while (!utility::isValidDate(year, month, day));
	std::chrono::year_month_day movieReleaseDate{
		std::chrono::year{year},
		std::chrono::month{static_cast<unsigned int>(month)},
		std::chrono::day{static_cast<unsigned int>(day)}
	};


	Movie newMovie(movieTitle, movieGenre, movieReleaseDate, movieLanguage);

	std::cout << "New Movie Created: \n";
	std::cout << "Title: " << newMovie.getTitle() << '\n';
	std::cout << "Genre: " << newMovie.getGenre() << '\n';
	std::cout << "Release Date: " << newMovie.getReleaseDate() << '\n';
	std::cout << "Language: " << newMovie.getLanguage() << '\n';

	std::cout << "Confirm creation of the movie? (y/n): ";
	char confirm;
	std::cin >> confirm;
	if (confirm == 'y' || confirm == 'Y')
	{
		std::ofstream outFile("../assets/objectData/movieObjects/" + newMovie.getTitle() + ".bin",
		                      std::ios::binary | std::ios::app);
		if (!outFile)
		{
			std::cerr << "Error: Unable to open file for writing." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(4));
			return;
		}
		if (!newMovie.saveToFile(outFile))
		{
			std::cerr << "Error: Failed to save movie to file." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(4));
			outFile.close();
			return;
		}
		outFile.close();
		std::cout << "Movie saved successfully!" << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	else
	{
		std::cout << "Movie creation cancelled." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

// Account create and save function
bool saveAccountToFile(const Account& account)
{
	std::string filePath = "../assets/objectData/accountObjects/" + account.getUsername() + ".bin";
	std::ofstream outFile(filePath, std::ios::binary);
	if (!outFile) return false;
	return account.saveToFile(outFile);
}

void createNewAccount()
{
	utility::displayTitleGraphic("../assets/titleGraphics/createObjectGraphics/createAccountTitleGraphic.txt");
	std::string username;
	std::string password;
	std::string confirmPassword;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do
	{
		std::cout << "Enter a username or exit by typing 'EXIT BACK': ";
		getline(std::cin, username);
		if (username.empty())
		{
			std::cout << "Username cannot be empty." << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << '\n';
		}
		else
		{
			if (username == "EXIT BACK")
			{
				std::cout << "Account creation cancelled." << '\n';
				std::this_thread::sleep_for(std::chrono::seconds(2));
				return;
			}
			if (utility::doesFileNameExists(username, "../assets/objectData/accountObjects/"))
			{
				std::cout << "Username already exists. Please choose a different username." << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << '\n';
			}
		}
	}
	while (username.empty() || utility::doesFileNameExists(username, "../assets/objectData/accountObjects/"));
	std::cout << '\n';
	do
	{
		std::cout << "Enter a password or exit by typing 'EXIT BACK': ";
		getline(std::cin, password);
		if (password == "EXIT BACK")
		{
			std::cout << "Account creation cancelled." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(2));
			return;
		}
		std::cout << "Confirm password: ";
		getline(std::cin, confirmPassword);
		if (!utility::isValidPassword(password))
		{
			std::cout <<
				"Password must be at least 8 characters long, contain at least one letter, one digit, and one special character."
				<< '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << '\n';
		}
		else if (password != confirmPassword)
		{
			std::cout << "Passwords do not match. Please try again." << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << '\n';
		}
	}
	while (!utility::isValidPassword(password) || password != confirmPassword);
	std::cout << '\n';

	std::cout << "Confirm account creation? (y/n): ";
	char confirm;
	std::cin >> confirm;
	if (confirm == 'y' || confirm == 'Y')
	{
		Account newAccount(username, password);
		if (saveAccountToFile(newAccount))
		{
			std::cout << "Account created successfully!" << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
		else
		{
			std::cerr << "Error: Account could not be saved to a file." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(4));
		}
	}
	else
	{
		std::cout << "Account creation cancelled." << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}
