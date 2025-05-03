#pragma once  
#include <string>

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
