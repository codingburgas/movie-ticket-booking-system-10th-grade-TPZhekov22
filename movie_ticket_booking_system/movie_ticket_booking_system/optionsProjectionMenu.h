#pragma once
#include <vector>
#include "cinemaObjects.h"

void selectSeatToBook(std::vector<std::vector<int>>& selectedSeats, MovieProjection& currentMovieProjection);
void unselectSeatToBook(std::vector<std::vector<int>>& selectedSeats);
void purchaseTicket(std::vector<std::vector<int>>& selectedSeats, MovieProjection& currentMovieProjection, Hall& currentHall, Cinema& currentCinema, City& currentCity);