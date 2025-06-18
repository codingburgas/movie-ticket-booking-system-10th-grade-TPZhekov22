#pragma once
#include "cinemaObjects.h"

void selectCity();
void selectCinema(City& currentCity);
void selectHall(Cinema& currentCinema, City& currentCity);
void selectMovieProjection(Hall& currentHall, Cinema& currentCinema, City& currentCity);