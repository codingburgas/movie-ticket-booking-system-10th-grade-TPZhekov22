#include "movie.h"

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
