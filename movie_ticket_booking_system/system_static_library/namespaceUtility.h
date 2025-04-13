#pragma once
#include <cstdint>

namespace utility
{
	void clear();
	extern bool exit;

	struct StructScene
	{
		enum EnumScene : std::uint8_t { Menu, View, ExitEnum };

		EnumScene currentScene = Menu;
	};

	extern StructScene scene;
}
