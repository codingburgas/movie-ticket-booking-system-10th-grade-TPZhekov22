#include "namespaceUtility.h"
#include <iostream>

namespace utility
{
    bool exit = false;
    StructScene scene;

    static void clearScreen()
    {
#if defined(_WIN32) || defined(_WIN64)
        std::system("cls");
#else
        std::system("clear");
#endif
    }
}