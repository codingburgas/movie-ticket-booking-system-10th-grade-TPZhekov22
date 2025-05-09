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
Movie(const std::string& movieTitle, const std::string& movieGenre, const std::string& movieDate, const std::string& movieLanguage); //Constructor 

// Getters for movie details  
const std::string& getTitle() const;  
const std::string& getGenre() const;  
const std::string& getReleaseDate() const;  
const std::string& getLanguage() const;  
};  



class movieProjection  
{  
private:  
Movie projectionMovie;
std::vector<std::vector<bool>> seats;  // 10x10 seating arrangement
int startingTime; // Using a 24 hour type Za izpolzvane pokusno DELETE LATER

public:  
movieProjection(const Movie& movie, int startingTime); //Constructor

bool bookTicket(int row, int col); // Book a ticket
void displaySeatPlan() const; // Display seating plan in movie prjection
};

class Hall
{
private:
	int ID;
	// movieProjectionClass

};

