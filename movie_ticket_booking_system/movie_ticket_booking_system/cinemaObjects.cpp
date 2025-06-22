#include <chrono>
#include "cinemaObjects.h"
#include <iostream>
#include "definitions.h"
#include "../system_static_library/namespaceUtility.h"

// Movie class implementation
Movie::Movie(const std::string& movieTitle, const std::string& movieGenre, const std::chrono::year_month_day& movieDate,const std::string& movieLanguage)
	: m_title(movieTitle), m_genre(movieGenre), m_releaseDate(movieDate), m_language(movieLanguage)
{
}

const std::string& Movie::getGenre() const
{
	return m_genre;
}

const std::string& Movie::getTitle() const
{
	return m_title;
}

std::chrono::year_month_day Movie::getReleaseDate() const 
{
	return m_releaseDate;
}

const std::string& Movie::getLanguage() const
{
	return m_language;
}

bool Movie::saveToFile(std::ostream& os) const {
	int year = static_cast<int>(m_releaseDate.year());
	unsigned month = static_cast<unsigned>(m_releaseDate.month());
	unsigned day = static_cast<unsigned>(m_releaseDate.day());
	return utility::writeString(os, m_title)
		&& utility::writeString(os, m_genre)
		&& os.write(reinterpret_cast<const char*>(&year), sizeof(year))
		&& os.write(reinterpret_cast<const char*>(&month), sizeof(month))
		&& os.write(reinterpret_cast<const char*>(&day), sizeof(day))
		&& utility::writeString(os, m_language);
}

std::optional<Movie> Movie::loadFromFile(std::istream& is) {
	std::string title, genre, language;
	int year;
	unsigned month, day;
	if (!utility::readString(is, title)) return std::nullopt;
	if (!utility::readString(is, genre)) return std::nullopt;
	is.read(reinterpret_cast<char*>(&year), sizeof(year));
	is.read(reinterpret_cast<char*>(&month), sizeof(month));
	is.read(reinterpret_cast<char*>(&day), sizeof(day));
	if (!utility::readString(is, language)) return std::nullopt;
	if (!is) return std::nullopt;
	std::chrono::year_month_day releaseDate{
		std::chrono::year{year},
		std::chrono::month{month},
		std::chrono::day{day}
	};
	return Movie(title, genre, releaseDate, language);
}

// MovieProjection class implementation
MovieProjection::MovieProjection(const Movie movie, int startingTime):
m_projectionMovie(movie), m_startingTime(startingTime)
{
	int tempTime = startingTime;
	while (tempTime < 0 || tempTime > 23)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid time. Please use a 24-hour format (0-23): ";
		std::cin >> tempTime;
	}
	this->m_startingTime = tempTime;

	m_seats.resize(SEAT_PLAN_ROWS, std::vector(SEAT_PLAN_COLS, false));
	for (size_t rows = 0; rows < SEAT_PLAN_ROWS; rows++)
	{
		for (size_t cols = 0; cols < SEAT_PLAN_COLS; cols++)
		{
			m_seats.at(rows).at(cols) = false;
		}
	}
}

bool MovieProjection::checkSeatAvailability(int selectedRow, int selectedCol) const
{
	if (m_seats.at(selectedRow - 1).at(selectedCol - 1) == true)
	{
		return true; // Seat is already booked
	}
	return false; // Seat is available
}

bool MovieProjection::bookTicket(int row, int col)
{
	if (row < 0 || row >= SEAT_PLAN_ROWS || col < 0 || col >= SEAT_PLAN_COLS)
	{
		std::cout << "Invalid seat number." << '\n';
		return false;
	}
	if (m_seats[row][col])
	{
		std::cout << "Seat already booked." << '\n';
		return false;
	}
	m_seats[row][col] = true;
	return true;
}

void MovieProjection::setProjectionTime(int projectionStartTime)
{
	int tempTime = projectionStartTime;
	std::cout << "Enter the starting time of the projection (0-23): ";
	std::cin >> tempTime;
	while (tempTime < 0 || tempTime > 23)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid time. Please use a 24-hour format (0-23): ";
		std::cin >> tempTime;
	}
	this->m_startingTime = tempTime;
}

void MovieProjection::displaySeatPlan() const  
{
   std::cout << "'X' - the seat is already taken" << '\n';
   std::cout << "'0' - the seat is available" << '\n';
   std::cout << '\n';
   std::cout << "                                          SCREEN" << '\n';
   std::cout << " _________________________________________________________________________________________" << '\n';
   std::cout << " |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << '\n'; //49
   std::cout << " -----------------------------------------------------------------------------------------" << '\n';
   std::cout << '\n';

   // Print top border
   std::cout << "             ";
   for (size_t col = 0; col < SEAT_PLAN_COLS; col++)
   {
	   std::cout << " -----";
   }
   std::cout << '\n';

   for (size_t row = 0; row < SEAT_PLAN_ROWS; row++)
   {
	   // Print row number (1-based, aligned)
	   std::cout << "         " << (row + 1 < 10 ? " " : "") << row + 1 << "  ";
	   // First line: seat symbol
	   for (size_t col = 0; col < SEAT_PLAN_COLS; col++)
	   {
		   std::cout << "|  ";
		   if (m_seats[row][col])
			   std::cout << "X";
		   else
			   std::cout << "0";
		   std::cout << "  ";
	   }
	   std::cout << "|" << '\n';

	   // Second line: column number
	   std::cout << "             ";
	   for (size_t col = 0; col < SEAT_PLAN_COLS; col++)
	   {
		   // Center the column number
		   int colNum = static_cast<int>(col) + 1;
		   if (colNum < 10)
			   std::cout << "|  " << colNum << "  ";
		   else
			   std::cout << "| " << colNum << "  ";
	   }
	   std::cout << "|" << '\n';

	   // Print bottom border of boxes
	   std::cout << "             ";
	   for (size_t col = 0; col < SEAT_PLAN_COLS; col++)
	   {
		   std::cout << " -----";
	   }
	   std::cout << '\n';
   }
}

int MovieProjection::getProjectionTime() const
{
	return m_startingTime;
}

const std::string& MovieProjection::getProjectionMovieTitle() const
{
	return m_projectionMovie.getTitle();
}

const std::string& MovieProjection::getProjectionMovieGenre() const
{
	return m_projectionMovie.getGenre();
}

std::chrono::year_month_day MovieProjection::getProjectionMovieReleaseDate() const
{
	return m_projectionMovie.getReleaseDate();
}

const std::string& MovieProjection::getProjectionMovieLanguage() const
{
	return m_projectionMovie.getLanguage();
}

bool MovieProjection::saveToFile(std::ostream& os) const
{
	// Save the Movie
	if (!m_projectionMovie.saveToFile(os)) return false;

	// Save the starting time
	os.write(reinterpret_cast<const char*>(&m_startingTime), sizeof(m_startingTime));
	if (!os) return false;

	// Save the seats vector
	size_t numRows = m_seats.size();
	os.write(reinterpret_cast<const char*>(&numRows), sizeof(numRows));
	if (!os) return false;
	for (const auto& row : m_seats)
	{
		size_t numCols = row.size();
		os.write(reinterpret_cast<const char*>(&numCols), sizeof(numCols));
		if (!os) return false;
		for (bool seat : row)
		{
			os.write(reinterpret_cast<const char*>(&seat), sizeof(seat));
			if (!os) return false;
		}
	}
	return true;
}

std::optional<MovieProjection> MovieProjection::loadFromFile(std::istream& is)
{
	// Load the Movie
	auto movieOpt = Movie::loadFromFile(is);
	if (!movieOpt) return std::nullopt;

	// Load the starting time
	int startingTime;
	is.read(reinterpret_cast<char*>(&startingTime), sizeof(startingTime));
	if (!is) return std::nullopt;

	// Load the seats vector
	size_t numRows;
	is.read(reinterpret_cast<char*>(&numRows), sizeof(numRows));
	if (!is) return std::nullopt;
	std::vector<std::vector<bool>> seats(numRows);
	for (size_t i = 0; i < numRows; ++i)
	{
		size_t numCols;
		is.read(reinterpret_cast<char*>(&numCols), sizeof(numCols));
		if (!is) return std::nullopt;
		seats[i].resize(numCols);
		for (size_t j = 0; j < numCols; ++j)
		{
			bool temp;
			is.read(reinterpret_cast<char*>(&temp), sizeof(bool));
			seats[i][j] = temp;
			if (!is) return std::nullopt;
		}
	}

	//Return the MovieProjection object
	MovieProjection proj(*movieOpt, startingTime);
	proj.m_seats = std::move(seats);
	return proj;
}

// Hall class implementation
Hall::Hall(int id) : m_ID(id)
{
}

bool Hall::addProjection(MovieProjection& movieProjection)
{
	if (m_projectionPlan.size() >= MAX_PROJECTION_SIZE)
	{
		std::cout << "Cannot add more projections. Maximum limit reached(15)." << '\n';
		return false;
	}
	m_projectionPlan.push_back(movieProjection);
	return true;
}

void Hall::displayProjectionCalendar() const
{
	std::cout << '\n';
	for (size_t temp = 0; temp < m_projectionPlan.size(); temp++)
	{
		std::cout << "#" << temp + 1 << " Movie projection: " << m_projectionPlan.at(temp).getProjectionMovieTitle() << '\n';
		std::cout << "Genre: " << m_projectionPlan.at(temp).getProjectionMovieGenre() << '\n';
		std::cout << "Release Date: " << m_projectionPlan.at(temp).getProjectionMovieReleaseDate() << '\n';
		std::cout << "Language: " << m_projectionPlan.at(temp).getProjectionMovieLanguage() << '\n';
		std::cout << "Projection Time: " << m_projectionPlan.at(temp).getProjectionTime() << ":00" << '\n';
	}
}

std::vector<MovieProjection>& Hall::getProjectionPlan()
{
	return m_projectionPlan;
}

int Hall::getHallID() const
{
	return m_ID;
}

size_t Hall::numberOfProjections() const
{
	return m_projectionPlan.size();
}

bool Hall::saveToFile(std::ostream& os) const
{
	// Save the ID
	os.write(reinterpret_cast<const char*>(&m_ID), sizeof(m_ID));
	if (!os) return false;

	// Save the projectionPlan vector
	size_t numProjections = m_projectionPlan.size();
	os.write(reinterpret_cast<const char*>(&numProjections), sizeof(numProjections));
	if (!os) return false;
	for (const auto& proj : m_projectionPlan)
	{
		if (!proj.saveToFile(os)) return false;
	}
	return true;
}

std::optional<Hall> Hall::loadFromFile(std::istream& is)
{
	// Load the ID
	int id;
	is.read(reinterpret_cast<char*>(&id), sizeof(id));
	if (!is) return std::nullopt;

	// Load the projectionPlan vector
	size_t numProjections;
	is.read(reinterpret_cast<char*>(&numProjections), sizeof(numProjections));
	if (!is) return std::nullopt;

	// Check if the number of movieProjections is within the limit
	std::vector<MovieProjection> projectionPlan;
	projectionPlan.reserve(numProjections);
	for (size_t i = 0; i < numProjections; ++i)
	{
		auto projOpt = MovieProjection::loadFromFile(is);
		if (!projOpt) return std::nullopt;
		projectionPlan.push_back(std::move(*projOpt));
	}

	// Return the Hall object
	Hall hall(id);
	hall.m_projectionPlan = std::move(projectionPlan);
	return hall;
}

// Cinema class implementation
Cinema::Cinema(const std::string& cinemaName) : m_name(cinemaName)
{
}

const std::string& Cinema::getCinemaName() const
{
	return m_name;
}

std::vector<Hall>& Cinema::getHallsVector()
{
	return m_halls;
}

void Cinema::addHall(const Hall& hall)
{
	m_halls.push_back(hall);
}

void Cinema::displayHallsID() const
{
	for (const auto& hall : m_halls)
	{
		std::cout << "Hall# " << hall.getHallID() << '\n';
	}
}

size_t Cinema::numberOfHalls() const
{
	return m_halls.size();
}

void Cinema::displayMovies() const
{
	for (const auto& hall : m_halls)
	{
		std::cout << "Hall ID: " << hall.getHallID() << '\n';
		hall.displayProjectionCalendar();
		std::cout << '\n';
		std::cout << '\n';
	}
}

bool Cinema::saveToFile(std::ostream& os) const
{
	// Save the name
	if (!utility::writeString(os, m_name)) return false;

	// Save the halls vector
	size_t numHalls = m_halls.size();
	os.write(reinterpret_cast<const char*>(&numHalls), sizeof(numHalls));
	if (!os) return false;
	for (const auto& hall : m_halls)
	{
		if (!hall.saveToFile(os)) return false;
	}
	return true;
}

std::optional<Cinema> Cinema::loadFromFile(std::istream& is)
{
	// Load the name
	std::string name;
	if (!utility::readString(is, name)) return std::nullopt;

	// Load the halls vector
	size_t numHalls;
	is.read(reinterpret_cast<char*>(&numHalls), sizeof(numHalls));
	if (!is) return std::nullopt;

	std::vector<Hall> halls;
	halls.reserve(numHalls);
	for (size_t i = 0; i < numHalls; ++i)
	{
		auto hallOpt = Hall::loadFromFile(is);
		if (!hallOpt) return std::nullopt;
		halls.push_back(std::move(*hallOpt));
	}

	// Return the Cinema object
	Cinema cinema(name);
	cinema.m_halls = std::move(halls);
	return cinema;
}

// City class implementation
City::City(const std::string& cityName) : m_name(cityName)
{
}

const std::string& City::getCityName() const
{
	return m_name;
}

std::vector<Cinema>& City::getCinemasVector()
{
	return m_cinemas;
}

void City::addCinema(Cinema& cinema)
{
	m_cinemas.push_back(cinema);
}

void City::displayCinemas() const  
{  
   int cinemaNumber = 1;  
   for (const auto& cinema : m_cinemas)  
   {  
       std::cout << "Cinema " << cinemaNumber << ": " << cinema.getCinemaName() << '\n';  
       cinemaNumber++;  
   }  
}

size_t City::numberOfCinemas() const
{
	return m_cinemas.size();
}

bool City::saveToFile(std::ostream& os) const
{
	// Save the city name
	if (!utility::writeString(os, m_name)) return false;

	// Save the cinemas vector
	size_t numCinemas = m_cinemas.size();
	os.write(reinterpret_cast<const char*>(&numCinemas), sizeof(numCinemas));
	if (!os) return false;
	for (const auto& cinema : m_cinemas)
	{
		if (!cinema.saveToFile(os)) return false;
	}
	return true;
}

std::optional<City> City::loadFromFile(std::istream& is)
{
	// Load the city name
	std::string name;
	if (!utility::readString(is, name)) return std::nullopt;

	// Load the cinemas vector
	size_t numCinemas;
	is.read(reinterpret_cast<char*>(&numCinemas), sizeof(numCinemas));
	if (!is) return std::nullopt;

	std::vector<Cinema> cinemas;
	cinemas.reserve(numCinemas);
	for (size_t i = 0; i < numCinemas; ++i)
	{
		auto cinemaOpt = Cinema::loadFromFile(is);
		if (!cinemaOpt) return std::nullopt;
		cinemas.push_back(std::move(*cinemaOpt));
	}

	City city(name);
	city.m_cinemas = std::move(cinemas);
	return city;
}