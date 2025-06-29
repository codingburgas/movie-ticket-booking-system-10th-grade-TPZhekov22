#pragma once
#include <chrono>
#include <string>
#include <ranges>

namespace utility
{
	/*struct StructScene
		{
			enum EnumScene : std::uint8_t { Menu, Cities ,Cinemas, ExitEnum };

			EnumScene currentScene = Menu;
		};

	extern StructScene scene;*/

	void clearScreen();
	void displayTitleGraphic(const std::string& file_link);
	void displayDate(std::chrono::year_month_day dateYearMonthDay);
	bool isLeapYear(int year);
	bool isValidDate(int year, int month, int day);

	extern bool exit;

	// String serialization helpers
	inline bool writeString(std::ostream& os, const std::string& str)
	{
		size_t strLength = str.size();
		os.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		if (!os) return false;
		std::streamsize streamLength = static_cast<std::streamsize>(strLength);
		os.write(str.data(), streamLength);
		return os.good();
	}

	inline bool readString(std::istream& is, std::string& str)
	{
		size_t strLength;
		is.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		if (!is) return false;
		str.resize(strLength);
		std::streamsize streamLength = static_cast<std::streamsize>(strLength);
		is.read(str.data(), streamLength);
		return is.good();
	}

	bool fileExists(const std::string& filePath);

	bool vectorLinearSearch(std::vector<int>& vec, int& target);
	bool vectorLinearSearch2D(std::vector<std::vector<int>>& vec, int target);
	bool vectorLinearSearchRow2D(std::vector<std::vector<int>>& vec, int specificRow, int value);

	bool removeFrom2DVectorRow(std::vector<std::vector<int>>& vec, int rowIndex, int value);

	bool is2DVectorEmpty(std::vector<std::vector<int>>& vec);

	void listAvailableMovies();
}
