#include <fstream>
#include "cinemaObjects.h"
#include "loadObjectData.h"
#include <iostream>
#include <optional>
#include <thread>
#include "accountObject.h"
#include "../system_static_library/namespaceUtility.h"

// Cities vector loading function
std::vector<City> loadCitiesFromFile()
{
	std::vector<City> cities;
	std::string fullPath = "../assets/objectData/cityObjects/cities.bin";

	std::ifstream inFile(fullPath, std::ios::binary);
	if (!inFile)
	{
		std::cerr << "Error: Unable to open file for reading at " << fullPath << '\n';
		return cities;
	}

	size_t numCities = 0;
	inFile.read(reinterpret_cast<char*>(&numCities), sizeof(numCities));
	if (!inFile)
	{
		std::cerr << "Error: Failed to read city count." << '\n';
		return cities;
	}

	for (size_t i = 0; i < numCities; ++i)
	{
		auto cityOpt = City::loadFromFile(inFile);
		if (!cityOpt)
		{
			std::cerr << "Error: Failed to load city from file." << '\n';
			break;
		}
		cities.push_back(std::move(*cityOpt));
	}

	inFile.close();
	return cities;
}

// Movie loading function
Movie loadMoviesFromFile(std::string& movieName)
{
	std::string movieFilePath = "../assets/objectData/movieObjects/" + movieName + ".bin";
	std::ifstream inFile(movieFilePath, std::ios::binary);
	if (!inFile)
	{
		std::cerr << "Error: Unable to open movie file for reading at " << movieFilePath << '\n';
		return Movie("error", "error", {}, "error");
	}
	auto movieOpt = Movie::loadFromFile(inFile);
	if (!movieOpt)
	{
		std::cerr << "Error: Failed to load movie from file." << '\n';
		return Movie("error", "error", {}, "error");
	}
	inFile.close();
	return *movieOpt;
}

// Account login and loading function
std::optional<Account> loadAccountFromFile(const std::string& username)
{
	std::string filePath = "../assets/objectData/accountObjects/" + username + ".bin";
	std::ifstream inFile(filePath, std::ios::binary);
	if (!inFile) return std::nullopt;
	return Account::loadFromFile(inFile);
}

Account logInAccount()
{
	std::string username;
	std::string password;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do
	{
		std::cout << '\n';
		std::cout << "Enter your username or cancel by typing 'EXIT BACK': ";
		std::getline(std::cin, username);
		if (username.empty())
		{
			std::cout << "Username cannot be empty." << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else
		{
			if (username == "EXIT BACK")
			{
				std::cout << "Login cancelled." << '\n';
				std::this_thread::sleep_for(std::chrono::seconds(2));
				return {};
			}
			if (!utility::doesFileNameExists(username, "../assets/objectData/accountObjects/"))
			{
				std::cout << "Error: Account with username '" << username << "' does not exist." << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
		}
	}
	while (username.empty() || !utility::doesFileNameExists(username, "../assets/objectData/accountObjects/"));

	auto accountOpt = loadAccountFromFile(username);
	Account account = *accountOpt;

	do
	{
		std::cout << '\n';
		std::cout << "Enter your password or cancel by typing 'EXIT BACK': ";
		std::getline(std::cin, password);
		if (password == "EXIT BACK")
		{
			std::cout << "Login cancelled." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(2));
			return {};
		}
		if (account.getPassword() != password)
		{
			std::cout << "Error: Incorrect password." << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
	while (account.getPassword() != password);
	return account;
}
