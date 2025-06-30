#pragma once
#include "accountObject.h"
#include "cinemaObjects.h"

void mainMenu(Account& currentAccount);
void cityMenu(Account& currentAccount, City& currentCity);
void cinemaMenu(Account& currentAccount, Cinema& currentCinema, City& currentCity);
void hallMenu(Account& currentAccount, Hall& currentHall, Cinema& currentCinema, City& currentCity);
void projectionMenu(Account& currentAccount, MovieProjection& currentMovieProjection, Hall& currentHall, Cinema& currentCinema, City& currentCity);

void displayAllMoviesInDirectory();
void manageAdmins();