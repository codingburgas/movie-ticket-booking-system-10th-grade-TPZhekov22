#pragma once
#include <vector>
#include "cinemaObjects.h"
#include "accountObject.h"

//Cities vector create and save functions
//void createNewCity();
bool saveCitiesToFile(const std::vector<City>& cities);

//Cinema create and save function
void createNewCinema(City& currentCity);

//Hall create and save function
void createNewHall(Cinema& currentCinema, City& currentCity);

//MovieProjection create and save function
void saveMovieProjection(Hall& currentHall, Cinema& currentCinema, City& currentCity, MovieProjection& updatedProjection);
void createNewMovieProjection(Hall& currentHall, Cinema& currentCinema, City& currentCity);

//Movie create and save function
void addNewMovie();

//Account save function
bool saveAccountToFile(const Account& account);