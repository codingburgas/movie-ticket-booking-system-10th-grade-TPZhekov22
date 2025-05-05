#pragma once  
#include <string>
#include <vector>
#include <iostream>

class Movie  
{  
private:  
const std::string title;  
const std::string genre;  
const std::string releaseDate;  
const std::string language;  

public:  
Movie(const std::string& movieTitle, const std::string& movieGenre, const std::string& movieDate, const std::string& movieLanguage);  

// Getters for movie details  
const std::string& getTitle() const;  
const std::string& getGenre() const;  
const std::string& getReleaseDate() const;  
const std::string& getLanguage() const;  
};  



class Projection  
{  
private:  
Movie projectionMovie;
std::vector<std::vector<bool>> seats;  // 10x10 seating arrangement
int startingTime; // Using a 24 hour type Za izpolzvane pokusno DELETE LATER

public:  
Projection(const Movie& movie, int startingTime) : projectionMovie(movie), startingTime(startingTime)
{  
	  
	for (size_t rows = 0; rows < 10; rows++)
	{  
		for (size_t cols = 0; cols < 10; cols++)
		{  
			seats[rows][cols] = false;
		}  
	}  
}  
bool bookTicket(int row, int col)
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
}; // Split the method definitions into a separate file DELETE LATER