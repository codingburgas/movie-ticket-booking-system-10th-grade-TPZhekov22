#pragma once
#include "accountObject.h"
#include "cinemaObjects.h"

void selectCity(Account& currentAccount);
void selectCinema(Account& currentAccount, City& currentCity);
void selectHall(Account& currentAccount, Cinema& currentCinema, City& currentCity);
void selectMovieProjection(Account& currentAccount, Hall& currentHall, Cinema& currentCinema, City& currentCity);