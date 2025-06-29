#pragma once
#include "cinemaObjects.h"

void deleteCinema(City& currentCity);
void deleteHall(Cinema& currentCinema, City& currentCity);
void deleteMovieProjection(Hall& currentHall, Cinema& currentCinema, City& currentCity);
void removeMovie();