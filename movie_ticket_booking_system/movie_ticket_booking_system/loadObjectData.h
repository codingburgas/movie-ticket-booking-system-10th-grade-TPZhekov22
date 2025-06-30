#pragma once
#include "accountObject.h"

// Cities vector loading function
std::vector<City> loadCitiesFromFile();

// Movie loading function
Movie loadMoviesFromFile(std::string& movieName);

// Account login and loading function
Account logInAccount();
std::optional<Account> loadAccountFromFile(const std::string& username);