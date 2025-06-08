#include "namespaceUtility.h"

namespace utility
{
    bool exit = false;
    StructScene scene;

    void clearScreen()
    {
#if defined(_WIN32) || defined(_WIN64)
        std::system("cls");
#else
        std::system("clear");
#endif
    }

    void displayTitleGraphic(const std::string& file_link)
    {
		if (std::ifstream file(file_link); file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				std::cout << line << '\n';
			}
			file.close();
		}
		else
		{
			std::cerr << "Unable to open file" << '\n';
		}
    }

	void displayDate(std::chrono::year_month_day dateYearMonthDay)
    {
	    std::chrono::year_month_day ymd = dateYearMonthDay;
	std::cout << static_cast<int>(ymd.year()) << '-'
		<< static_cast<unsigned>(ymd.month()) << '-'
		<< static_cast<unsigned>(ymd.day()) << '\n';
    }

	bool isLeapYear(int year) {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	bool isValidDate(int year, int month, int day) {
		if (month < 1 || month > 12) return false;
		if (day < 1) return false;

		switch (month) {
		case 2:
			if (isLeapYear(year))
				return day <= 29;
			else
				return day <= 28;
		case 4: case 6: case 9: case 11:
			return day <= 30;
		default:
			return day <= 31;
		}
	}
	
}

// Example usage of serialization and deserialization of MOVIE objects. DELETE LATER
/*
// Serialization
std::ofstream ofs("movie.dat", std::ios::binary);
if (!movie.save(ofs)) {
	// Handle error
}

// Deserialization
std::ifstream ifs("movie.dat", std::ios::binary);
auto loadedMovieOpt = Movie::load(ifs);
if (loadedMovieOpt) {
	Movie loadedMovie = *loadedMovieOpt;
	// Use loadedMovie
}
else {
	// Handle error
}*/


// Example usage of serialization and deserialization of MOVIE PROJECTION objects. DELETE LATER
/*
// Serialization
std::ofstream ofs("projection.dat", std::ios::binary);
if (!projection.saveToFile(ofs)) {
	// Handle error
}

// Deserialization
std::ifstream ifs("projection.dat", std::ios::binary);
auto loadedProjectionOpt = MovieProjection::loadFromFile(ifs);
if (loadedProjectionOpt) {
	MovieProjection loadedProjection = *loadedProjectionOpt;
	// Use loadedProjection
}
else {
	// Handle error
} */

// Example usage of serialization and deserialization of HALL objects. DELETE LATER
/*
// Serialization
std::ofstream ofs("hall.dat", std::ios::binary);
if (!hall.saveToFile(ofs)) {
	// Handle error
}

// Deserialization
std::ifstream ifs("hall.dat", std::ios::binary);
auto loadedHallOpt = Hall::loadFromFile(ifs);
if (loadedHallOpt) {
	Hall loadedHall = *loadedHallOpt;
	// Use loadedHall
}
else {
	// Handle error
}
*/

// Example usage of serialization and deserialization of CINEMA objects. DELETE LATER
/*
// Serialization
std::ofstream ofs("cinema.dat", std::ios::binary);
if (!cinema.saveToFile(ofs)) {
	// Handle error
}

// Deserialization
std::ifstream ifs("cinema.dat", std::ios::binary);
auto loadedCinemaOpt = Cinema::loadFromFile(ifs);
if (loadedCinemaOpt) {
	Cinema loadedCinema = *loadedCinemaOpt;
	// Use loadedCinema
} else {
	// Handle error
}
*/

// Example usage of serialization and deserialization of CITY objects. DELETE LATER
/*
 // Serialization
std::ofstream ofs("city.dat", std::ios::binary);
if (!city.saveToFile(ofs)) {
	// Handle error
}

// Deserialization
std::ifstream ifs("city.dat", std::ios::binary);
auto loadedCityOpt = City::loadFromFile(ifs);
if (loadedCityOpt) {
	City loadedCity = *loadedCityOpt;
	// Use loadedCity
} else {
	// Handle error
}
 */