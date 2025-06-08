#include "createNewObjects.h"
#include "cinemaObjects.h"
#include "../system_static_library/namespaceUtility.h"
#include <fstream>
#include <iostream>

//Cities vector create and save functions
/*
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
	std::cin >> newCityName;

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
*/

void saveCitiesToFile(const std::vector<City>& cities)
{
    std::string fullPath = "../assets/objectData/cityObjects/cities.bin";

    std::ofstream outFile(fullPath, std::ios::binary);
    if (!outFile)
    {
        std::cerr << "Error: Unable to open file for writing at " << fullPath << '\n';
        return;
    }

    size_t numCities = cities.size();
    outFile.write(reinterpret_cast<const char*>(&numCities), sizeof(numCities));
    if (!outFile) {
        std::cerr << "Error: Failed to write city count.\n";
        return;
    }

    for (const auto& city : cities)
    {
        if (!city.saveToFile(outFile))
        {
            std::cerr << "Error: Failed to save city to file.\n";
            outFile.close();
            return;
        }
    }

    outFile.close();
    std::cout << "Cities saved successfully to " << fullPath << '\n';
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