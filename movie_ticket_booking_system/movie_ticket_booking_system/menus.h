#pragma once
#include "cinemaObjects.h"

void mainMenu();
void cityMenu(City& currentCity);
void cinemaMenu(Cinema& currentCinema, City& currentCity);
void hallMenu(Hall& currentHall, Cinema& currentCinema, City& currentCity);
void projectionMenu(MovieProjection& currentMovieProjection, Hall& currentHall, Cinema& currentCinema, City& currentCity);