#pragma once
#include <vector>
#include "cinemaObjects.h"

//Cities vector create and save functions
void createNewCity();
bool saveCitiesToFile(const std::vector<City>& cities);

//Cinema create and save function
void createNewCinema(City& currentCity);

// Hall creation function
void createNewHall(Cinema& currentCinema, City& currentCity);

//Movie creation function
void createNewMovie();