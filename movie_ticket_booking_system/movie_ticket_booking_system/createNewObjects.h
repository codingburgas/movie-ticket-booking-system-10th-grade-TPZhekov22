#pragma once
#include <vector>
#include "cinemaObjects.h"

//Cities vector create and save functions
void createNewCity();
bool saveCitiesToFile(const std::vector<City>& cities);

void createNewCinema(City& currentCity);

//Movie creation function
void createNewMovie();