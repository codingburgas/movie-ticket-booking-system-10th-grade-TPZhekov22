#pragma once  
#include <string>
#include <vector>
#include <iostream>

#define SEAT_PLAN_ROWS 10
#define SEAT_PLAN_COLS 10

// Movie class declaration
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
const std::string& getTitle() const; // Get the title of the movie
const std::string& getGenre() const; // Get the genre of the movie
const std::string& getReleaseDate() const;  // Get the release date of the movie
const std::string& getLanguage() const;  // Get the language of the movie
};  

// MovieProjection class declaration
class MovieProjection  
{  
private:  
   Movie projectionMovie;
   std::vector<std::vector<bool>> seats;  
   int startingTime;

public:  
   MovieProjection(const Movie& movie, int startingTime);  

   
   void displaySeatPlan() const; // Display the seat plan for the projection
   int getProjectionTime() const; // Get the projection time
   const std::string& getProjectionMovieTitle() const; // Get the title of the movie
   const std::string& getProjectionMovieGenre() const; // Get the genre of the movie
   const std::string& getProjectionMovieReleaseDate() const; // Get the release date of the movie
   const std::string& getProjectionMovieLanguage() const; // Get the language of the movie

   bool bookTicket(int row, int col); // Book a ticket for a specific seat
   void setProjectionTime(int projectionStartTime); // Set the projection time
};

// Hall class declaration
class Hall
{
private:
	const int ID;
	std::vector<MovieProjection> projectionPlan;
public:
	Hall(int id);

	void addProjection(const Movie& movie); // Add a projection to the hall
	void displayProjectionCalendar() const; // Display the hall's projection plan
	int getHallID() const; // Get the ID of the hall
};

// Cinema class declaration
class Cinema
{
private:
	std::string name;
	std::vector<Hall> halls;
public:
	Cinema(const std::string& cinemaName); // Constructor to initialize the cinema with a name and number of halls

	void addHall(const Hall& hall); // Add a hall to the cinema
	const std::string& getCinemaName() const; // Get the name of the cinema
	void displayHallsID() const; // Display all halls in the cinema
	void displayMovies() const; // Display all movies in the cinema
};

//City class declaration
class City
{
	private:
		std::string name;
		std::vector<Cinema> cinemas;
	public:
		City(const std::string& cityName); // Constructor to initialize the city with a name
		const std::string& getCityName() const; // Get the name of the city
		void addCinema(const Cinema& cinema); // Add a cinema to the city
		void displayCinemas() const; // Display all cinemas in the city
};