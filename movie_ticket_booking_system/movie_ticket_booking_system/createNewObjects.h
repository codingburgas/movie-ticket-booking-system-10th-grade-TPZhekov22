#pragma once
#include <vector>
#include "cinemaObjects.h"

//Cities vector create and save functions
//void createNewCity();
void saveCitiesToFile(const std::vector<City>& cities);

//Movie creation function
void createNewMovie();