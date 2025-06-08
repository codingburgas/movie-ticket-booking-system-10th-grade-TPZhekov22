#include "createNewObjects.h"
#include "cinemaObjects.h"
#include <fstream>

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
