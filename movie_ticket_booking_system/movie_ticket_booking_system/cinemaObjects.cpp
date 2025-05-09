#include "cinemaObjects.h"

#define seatPlanRows = 10
#define seatPlanCols = 10

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


movieProjection::movieProjection(const Movie& movie, int startingTime) : projectionMovie(movie), startingTime(startingTime)
{

	for (size_t rows = 0; rows < 10; rows++)
	{
		for (size_t cols = 0; cols < 10; cols++)
		{
			seats[rows][cols] = false;
		}
	}
}

bool movieProjection::bookTicket(int row, int col)
{
	if (row < 0 || row >= 10 || col < 0 || col >= 10)
	{
		std::cout << "Invalid seat number." << std::endl;
		return false;
	}
	if (seats[row][col])
	{
		std::cout << "Seat already booked." << std::endl;
		return false;
	}
	seats[row][col] = true;
	return true;
}

void movieProjection::displaySeatPlan() const
{
	for (size_t row = 0; row < 10; row++)
	{
		for (size_t col = 0; col < 10; col++)
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
		std::cout << std::endl;
	}
}