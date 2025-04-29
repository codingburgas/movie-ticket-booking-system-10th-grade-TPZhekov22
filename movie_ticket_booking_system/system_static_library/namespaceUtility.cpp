#include "namespaceUtility.h"
#include <iostream>
#include <string>
#include <fstream>

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
}
