#include <fstream>
#include "cinemaObjects.h"
#include "loadObjectData.h"
#include <iostream>

// Cities vector loading function
std::vector<City> loadCitiesFromFile()
{
    std::vector<City> cities;
    std::string fullPath = "../assets/objectData/cityObjects/cities.bin";

    std::ifstream inFile(fullPath, std::ios::binary);
    if (!inFile)
    {
        std::cerr << "Error: Unable to open file for reading at " << fullPath << '\n';
        return cities;
    }

    size_t numCities = 0;
    inFile.read(reinterpret_cast<char*>(&numCities), sizeof(numCities));
    if (!inFile)
    {
        std::cerr << "Error: Failed to read city count." << '\n';
        return cities;
    }

    for (size_t i = 0; i < numCities; ++i)
    {
        auto cityOpt = City::loadFromFile(inFile);
        if (!cityOpt)
        {
            std::cerr << "Error: Failed to load city from file." << '\n';
            break;
        }
        cities.push_back(std::move(*cityOpt));
    }

    inFile.close();
    return cities;
}

// Movie loading function
Movie loadMoviesFromFile(std::string& movieName)
{

	std::string movieFilePath = "../assets/objectData/movieObjects/" + movieName + ".bin";
	std::ifstream inFile(movieFilePath, std::ios::binary);
	if (!inFile)
	{
		std::cerr << "Error: Unable to open movie file for reading at " << movieFilePath << '\n';
		return Movie("", "", {}, "");
	}
	auto movieOpt = Movie::loadFromFile(inFile);
	if (!movieOpt)
	{
		std::cerr << "Error: Failed to load movie from file." << '\n';
		return Movie("", "", {}, "");
	}
	inFile.close();
	return *movieOpt;
}