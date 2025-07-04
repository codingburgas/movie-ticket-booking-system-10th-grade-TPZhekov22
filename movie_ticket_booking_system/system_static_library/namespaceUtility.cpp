#include "namespaceUtility.h"
#include <chrono>
#include <string>
#include <iostream>
#include <fstream>
#include <ranges>
#include <algorithm>
#include <filesystem>
#include <cctype>

namespace utility
{
#define MIN_PASSWORD_LENGTH 8
	//StructScene scene;
	bool exit = false;

	void clearScreen()
	{
#if defined(_WIN32) || defined(_WIN64)
		std::system("cls");
#else
		std::system("clear");
#endif
	}

	void displayTitleGraphic(const std::string& file_link)
	{
		if (std::ifstream file(file_link); file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				std::cout << line << '\n';
			}
			file.close();
		}
		else
		{
			std::cerr << "Unable to open file" << '\n';
		}
	}

	void displayDate(std::chrono::year_month_day dateYearMonthDay)
	{
		std::chrono::year_month_day ymd = dateYearMonthDay;
		std::cout << static_cast<int>(ymd.year()) << '-'
			<< static_cast<unsigned>(ymd.month()) << '-'
			<< static_cast<unsigned>(ymd.day()) << '\n';
	}

	bool isLeapYear(int year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	bool isValidDate(int year, int month, int day)
	{
		if (month < 1 || month > 12) return false;
		if (day < 1) return false;

		switch (month)
		{
		case 2:
			{
				if (isLeapYear(year))
					return day <= 29;
				return day <= 28;
			}
		case 4:
		case 6:
		case 9:
		case 11:
			return day <= 30;
		default:
			return day <= 31;
		}
	}

	bool fileExists(const std::string& filePath)
	{
		std::ifstream file(filePath);
		return file.good();
	}

	bool is2DVectorEmpty(std::vector<std::vector<int>>& vec)
	{
		return std::ranges::all_of(vec, [](const auto& row) { return row.empty(); });
	}

	bool vectorLinearSearch(std::vector<int>& vec, int& target)
	{
		for (int temp : vec)
		{
			if (temp == target)
			{
				return true;
			}
		}
		return false;
	}

	bool vectorLinearSearch2D(std::vector<std::vector<int>>& vec, int target)
	{
		for (auto& row : vec)
		{
			if (std::ranges::find(row, target) != row.end())
			{
				return true;
			}
		}
		return false;
	}

	bool vectorLinearSearchRow2D(std::vector<std::vector<int>>& vec, int specificRow, int value)
	{
		auto& row = vec.at(specificRow);
		return std::ranges::find(row, value) != row.end();
	}

	bool removeFrom2DVectorRow(std::vector<std::vector<int>>& vec, int rowIndex, int value)
	{
		if (rowIndex < 0 || rowIndex >= static_cast<int>(vec.size()))
			return false;

		auto& row = vec.at(rowIndex);
		auto it = std::ranges::find(row, value);
		if (it != row.end())
		{
			row.erase(it);
			return true;
		}
		return false;
	}

	void listAvailableMovies()
	{
		for (const auto& entry : std::filesystem::directory_iterator("../assets/objectData/movieObjects/"))
		{
			if (entry.path().extension() == ".bin")
			{
				std::cout << "- " << entry.path().stem().string() << '\n';
			}
		}
	}

	void listAvailableAccounts()
	{
		for (const auto& entry : std::filesystem::directory_iterator("../assets/objectData/accountObjects/"))
		{
			if (entry.path().extension() == ".bin")
			{
				std::cout << "- " << entry.path().stem().string() << '\n';
			}
		}
	}

	bool doesFileNameExists(const std::string& username, const std::string& dirPath)
	{
		for (const auto& entry : std::filesystem::directory_iterator(dirPath))
		{
			if (entry.is_regular_file())
			{
				std::string filename = entry.path().filename().string();
				if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".bin")
				{
					std::string nameOnly = filename.substr(0, filename.size() - 4);
					if (nameOnly == username)
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool isValidPassword(const std::string& password)
	{
		if (password.length() < MIN_PASSWORD_LENGTH) return false;

		bool hasLetter = false;
		bool hasDigit = false;
		bool hasSpecial = false;

		for (const char ch : password)
		{
			if (std::isalpha(static_cast<unsigned char>(ch))) hasLetter = true;
			else if (std::isdigit(static_cast<unsigned char>(ch))) hasDigit = true;
			else hasSpecial = true;
		}
		return hasLetter && hasDigit && hasSpecial;
	}
}
