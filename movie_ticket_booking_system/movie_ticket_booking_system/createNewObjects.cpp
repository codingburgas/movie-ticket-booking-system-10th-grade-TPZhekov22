#include "createNewObjects.h"
#include "cinemaObjects.h"
#include "../system_static_library/namespaceUtility.h"
#include <fstream>
#include <iostream>

#include "loadObjectData.h"

//Cities vector create and save functions

void createNewCity()
{
	std::string newCityName;
    std::string fullPath = "../assets/objectData/cityObjects/cities.bin";
    std::vector<City> cities;
    {
        std::ifstream inFile(fullPath, std::ios::binary);
        if (inFile)
        {
            size_t numCities = 0;
            inFile.read(reinterpret_cast<char*>(&numCities), sizeof(numCities));
            for (size_t i = 0; i < numCities; ++i)
            {
	            if (auto cityOpt = City::loadFromFile(inFile))
                    cities.push_back(std::move(*cityOpt));
            }
        }
    }

	std::cout << "Enter the name of the new city: ";
	std::getline(std::cin, newCityName);

	City* newCity = new City(newCityName);
    cities.push_back(*newCity);
	delete newCity;
	std::cout << "City " << newCityName << " created successfully!" << '\n';
	for (size_t temp = 0; temp < cities.size(); temp++)
	{
		std::cout << "City #" << temp + 1 <<": " << cities[temp].getCityName() << '\n';
	}
    saveCitiesToFile(cities);
}

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
    if (!outFile) {
        std::cerr << "Error: Failed to write city count.\n";
        outFile.close();
        return false;
    }

    for (const auto& city : cities)
    {
        if (!city.saveToFile(outFile))
        {
            std::cerr << "Error: Failed to save city to file.\n";
            outFile.close();
            return false;
        }
    }

    outFile.close();
    std::cout << "Cities saved successfully to " << fullPath << '\n';
    return true;
}

//Cinema create and save function
void createNewCinema(City& currentCity)
{
std::string newCinemaName;
std::cout << "Enter the name of the cinema: ";
std::cin.ignore();
std::getline(std::cin, newCinemaName);

Cinema newCinema(newCinemaName);

std::cout << "Name: " << newCinema.getCinemaName() << "\n";
std::cout << "Confirm creation of the cinema? (y/n): \n";
char confirm;
std::cin >> confirm;
utility::clearScreen();
if (confirm == 'y' || confirm == 'Y')
{
		currentCity.addCinema(newCinema);

       std::string fullPath = "../assets/objectData/cityObjects/cities.bin";
       std::vector<City> cities;
       {
           std::ifstream inFile(fullPath, std::ios::binary);
           if (inFile)
           {
               size_t numCities = 0;
               inFile.read(reinterpret_cast<char*>(&numCities), sizeof(numCities));
               for (size_t i = 0; i < numCities; ++i)
               {
                   if (auto cityOpt = City::loadFromFile(inFile))
                       cities.push_back(std::move(*cityOpt));
               }
           }
           else
           {
			   std::cerr << "Error: Unable to open file for reading at " << fullPath << '\n';
			   return;
           }
       }

       for (auto& city : cities)
       {
           if (city.getCityName() == currentCity.getCityName())
           {
               city = currentCity;
               break;
           }
       }

       saveCitiesToFile(cities);

       if (saveCitiesToFile(cities)) {
           std::cout << "Cinema created and saved successfully!\n";
       }
       else {
           std::cerr << "Error: Cinema was created but not saved to file.\n";
       }
}
else
{
	std::cout << "Cinema creation cancelled.\n";
}
}

// Hall create and save function
void createNewHall(Cinema& currentCinema, City& currentCity)
{
    Hall newHall(static_cast<int>(currentCinema.numberOfHalls()) + 1);
    std::cout << "New hall with ID " << newHall.getHallID() << "\n";
    std::cout << "Confirm creation of the hall? (y/n): ";
    char confirm;
    std::cin >> confirm;
    if (confirm == 'y' || confirm == 'Y')
    {
        currentCinema.addHall(newHall);

        for (auto& cinema : currentCity.getCinemasVector()) {
            if (cinema.getCinemaName() == currentCinema.getCinemaName()) {
                cinema = currentCinema;
                break;
            }
        }

        std::vector<City> cities;
        std::ifstream inFile("../assets/objectData/cityObjects/cities.bin", std::ios::binary);
        if (inFile) {
            size_t numCities = 0;
            inFile.read(reinterpret_cast<char*>(&numCities), sizeof(numCities));
            for (size_t i = 0; i < numCities; ++i) {
                if (auto cityOpt = City::loadFromFile(inFile)) {
                    cities.push_back(std::move(*cityOpt));
                }
            }
            inFile.close();
        }

        for (auto& city : cities) {
            if (city.getCityName() == currentCity.getCityName()) {
                city = currentCity;
                break;
            }
        }

        if (saveCitiesToFile(cities)) {
            std::cout << "Hall created and saved successfully!\n";
        }
        else {
            std::cerr << "Error: Hall was created but not saved to file.\n";
        }
    }
    else
    {
        std::cout << "Hall creation cancelled.\n";
    }
}

//Movie creation and save function
void createNewMovie()
{
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
    do {
        std::cout << "Enter release date (YYYY MM DD): ";
        std::cin >> year >> month >> day;
        if (!utility::isValidDate(year, month, day)) {
            std::cout << "Invalid date. Please try again.\n";
        }
    } while (!utility::isValidDate(year, month, day));
    std::chrono::year_month_day movieReleaseDate{
        std::chrono::year{year},
        std::chrono::month{static_cast<unsigned int>(month)},
        std::chrono::day{static_cast<unsigned int>(day)}
    };

	

	Movie newMovie(movieTitle, movieGenre, movieReleaseDate, movieLanguage);

    std::cout << "New Movie Created: \n";
    std::cout << "Title: " << newMovie.getTitle() << "\n";
    std::cout << "Genre: " << newMovie.getGenre() << "\n";
    std::cout << "Release Date: " << newMovie.getReleaseDate() << "\n";
	std::cout << "Language: " << newMovie.getLanguage() << "\n";

	std::cout << "Confirm creation of the movie? (y/n): ";
	char confirm;
	std::cin >> confirm;
	if (confirm == 'y' || confirm == 'Y')
	{
		std::ofstream outFile("../assets/objectData/movieObjects/" + newMovie.getTitle() + ".bin", std::ios::binary | std::ios::app);
		if (!outFile)
		{
			std::cerr << "Error: Unable to open file for writing.\n";
			return;
		}
		if (!newMovie.saveToFile(outFile))
		{
			std::cerr << "Error: Failed to save movie to file.\n";
			outFile.close();
			return;
		}
		outFile.close();
		std::cout << "Movie saved successfully!\n";
	}
	else
	{
		std::cout << "Movie creation cancelled.\n";
        return;
	}
}