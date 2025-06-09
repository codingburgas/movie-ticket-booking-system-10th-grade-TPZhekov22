#include "namespaceUtility.h"

namespace utility
{
    bool exit = false;
    StructScene scene;

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

	bool isLeapYear(int year) {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	bool isValidDate(int year, int month, int day) {
		if (month < 1 || month > 12) return false;
		if (day < 1) return false;

		switch (month) {
		case 2:
			if (isLeapYear(year))
				return day <= 29;
			else
				return day <= 28;
		case 4: case 6: case 9: case 11:
			return day <= 30;
		default:
			return day <= 31;
		}
	}
	
}