#pragma once
#include <chrono>
#include <string>
#include <vector>
#include <optional>

// Movie class declaration
class Movie
{
	std::string m_title;
	std::string m_genre;
	std::chrono::year_month_day m_releaseDate;
	std::string m_language;

public:
	Movie(const std::string& movieTitle, const std::string& movieGenre, const std::chrono::year_month_day& movieDate,
	      const std::string& movieLanguage);

	const std::string& getTitle() const;
	const std::string& getGenre() const;
	std::chrono::year_month_day getReleaseDate() const;
	const std::string& getLanguage() const;

	// Serialization methods for saving and loading movie objects
	bool saveToFile(std::ostream& os) const;
	static std::optional<Movie> loadFromFile(std::istream& is);
};

// MovieProjection class declaration
class MovieProjection
{
	Movie m_projectionMovie;
	std::vector<std::vector<bool>> m_seats;
	int m_startingTime;

public:
	MovieProjection(const Movie movie, int startingTime);


	void displaySeatPlan() const; // Display the seat plan for the projection
	int getProjectionTime() const; // Get the projection time
	const std::string& getProjectionMovieTitle() const; // Get the title of the movie
	const std::string& getProjectionMovieGenre() const; // Get the genre of the movie
	std::chrono::year_month_day getProjectionMovieReleaseDate() const; // Get the release date of the movie
	const std::string& getProjectionMovieLanguage() const; // Get the language of the movie

	bool bookTicket(int row, int col); // Book a ticket for a specific seat     //MODIFY TO USE 2D VECTOR std::vector<std::vector<int>> selectedSeats;
	bool checkSeatAvailability(int selectedRow, int selectedCol) const; // Check if a seat is available
	void setProjectionTime(int projectionStartTime); // Set the projection time

	bool saveToFile(std::ostream& os) const;
	static std::optional<MovieProjection> loadFromFile(std::istream& is);
};

// Hall class declaration
class Hall
{
	int m_ID;
	std::vector<MovieProjection> m_projectionPlan;

public:
	Hall(int id);

	bool addProjection(MovieProjection& movieProjection); // Add a projection to the hall
	std::vector<MovieProjection>& getProjectionPlan(); // Get the projection plan of the hall
	void displayProjectionCalendar() const; // Display the hall's projection plan
	int getHallID() const; // Get the ID of the hall
	size_t numberOfProjections() const; // Get the number of projections in the hall

	bool saveToFile(std::ostream& os) const;
	static std::optional<Hall> loadFromFile(std::istream& is);
};

// Cinema class declaration
class Cinema
{
	std::string m_name;
	std::vector<Hall> m_halls;

public:
	Cinema(const std::string& cinemaName); // Constructor to initialize the cinema with a name and number of halls

	void addHall(const Hall& hall); // Add a hall to the cinema
	const std::string& getCinemaName() const; // Get the name of the cinema
	std::vector<Hall>& getHallsVector(); // Get the halls in the cinema
	size_t numberOfHalls() const; // Get the number of halls in the cinema
	void displayHallsID() const; // Display all halls in the cinema
	void displayMovies() const; // Display all movies in the cinema

	bool saveToFile(std::ostream& os) const;
	static std::optional<Cinema> loadFromFile(std::istream& is);
};

//City class declaration
class City
{
	std::string m_name;
	std::vector<Cinema> m_cinemas;

public:
	City(const std::string& cityName); // Constructor to initialize the city with a name
	const std::string& getCityName() const; // Get the name of the city
	std::vector<Cinema>& getCinemasVector(); // Get the cinemas in the city
	void displayCinemas() const; // Display all cinemas in the city
	void addCinema(Cinema& cinema); // Add a cinema to the city
	size_t numberOfCinemas() const; // Get the number of cinemas in the city

	bool saveToFile(std::ostream& os) const;
	static std::optional<City> loadFromFile(std::istream& is);
};