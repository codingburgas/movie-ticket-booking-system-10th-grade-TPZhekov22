#include "cinemaObjects.h"


// Movie class implementation
Movie::Movie(const std::string& movieTitle, const std::string& movieGenre, const std::string& movieDate, const std::string& movieLanguage)
	: title(movieTitle), genre(movieGenre), releaseDate(movieDate), language(movieLanguage)
{}

const std::string& Movie::getGenre() const
{
	return genre;
}

const std::string& Movie::getTitle() const
{
	return title;
}

const std::string& Movie::getReleaseDate() const
{
	return releaseDate;
}

const std::string& Movie::getLanguage() const
{
	return language;
}

// MovieProjection class implementation
MovieProjection::MovieProjection(const Movie& movie, int startingTime) : projectionMovie(movie), startingTime(startingTime)
{
	int tempTime = startingTime;
	while (tempTime < 0 || tempTime > 23)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid time. Please use a 24-hour format (0-23): ";
		std::cin >> tempTime;
	}
	this->startingTime = tempTime;

for (size_t rows = 0; rows < SEAT_PLAN_ROWS; rows++)
{
	for (size_t cols = 0; cols < SEAT_PLAN_COLS; cols++)
	{
		seats[rows][cols] = false;
	}
}
}

bool MovieProjection::bookTicket(int row, int col)
{
	if (row < 0 || row >= SEAT_PLAN_ROWS || col < 0 || col >= SEAT_PLAN_COLS)
	{
		std::cout << "Invalid seat number." << '\n';
		return false;
	}
	if (seats[row][col])
	{
		std::cout << "Seat already booked." << '\n';
		return false;
	}
	seats[row][col] = true;
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
	this->startingTime = tempTime;
}

void MovieProjection::displaySeatPlan() const
{
	for (size_t row = 0; row < SEAT_PLAN_ROWS; row++)
	{
		for (size_t col = 0; col < SEAT_PLAN_COLS; col++)
		{
			if (seats[row][col] == true)
			{
				std::cout << "#";
			}
			else
			{
				std::cout << "0";
			}
		}
		std::cout << '\n';
	}
}

int MovieProjection::getProjectionTime() const
{
	return startingTime;
}

const std::string& MovieProjection::getProjectionMovieTitle() const
{
	return projectionMovie.getTitle();
}

const std::string& MovieProjection::getProjectionMovieGenre() const
{
	return projectionMovie.getGenre();
}

const std::string& MovieProjection::getProjectionMovieReleaseDate() const
{
	return projectionMovie.getReleaseDate();
}

const std::string& MovieProjection::getProjectionMovieLanguage() const
{
	return projectionMovie.getLanguage();
}

// Hall class implementation
Hall::Hall(const int id) : ID(id) {}

void Hall::addProjection(const MovieProjection& projection)
{
	projectionPlan.push_back(projection);
}

void Hall::displayProjectionCalendar() const
{
	std::cout << "Projection Calendar for hall: " << ID << '\n';
	for (size_t temp = 0; temp < projectionPlan.size(); temp++) 
	{
		std::cout << temp << "# Movie projection: " << projectionPlan.at(temp).getProjectionMovieTitle() << '\n';
	}
}

int Hall::getHallID() const
{
	return ID;
}