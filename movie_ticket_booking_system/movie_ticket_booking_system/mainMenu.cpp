#include <iostream>
#include <fstream>
#include <string>

void mainMenu()
{
	if (std::ifstream file(""); file.is_open())
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

	std::cout << "1: View Timeline" << '\n';
	std::cout << "2: Exit" << '\n';
}
