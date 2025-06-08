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

    // String serialization helpers
    inline bool writeString(std::ostream& os, const std::string& str) {
        size_t strLength = str.size();
        os.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
        if (!os) return false;
        os.write(str.data(), strLength);
        return os.good();
    }

    inline bool readString(std::istream& is, std::string& str) {
        size_t strLength;
        is.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
        if (!is) return false;
        str.resize(strLength);
        is.read(str.data(), strLength);
        return is.good();
    }
}
