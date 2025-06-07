#pragma once
#include <cstdint>
#include <string>
#include <iostream>

namespace utility
{
	struct StructScene
		{
			enum EnumScene : std::uint8_t { Menu, Cities ,Cinemas, ExitEnum };

			EnumScene currentScene = Menu;
		};

	extern StructScene scene;
	void clearScreen();
	void displayTitleGraphic(const std::string& file_link);

	extern bool exit;

	// String serialization
	inline bool writeString(std::ostream& os, const std::string& str);
	inline bool readString(std::istream& is, std::string& str);
}
