#pragma once
#include <cstdint>
#include <string>

namespace utility
{
	struct StructScene
		{
			enum EnumScene : std::uint8_t { Menu, Cinemas, ExitEnum };

			EnumScene currentScene = Menu;
		};

	extern StructScene scene;
	void clearScreen();
	void displayTitleGraphic(const std::string& file_link);

	extern bool exit;
}
