#include "manager.h"
#include "../system_static_library/windowManager.h"

int main()
{


	while (!WindowShouldClose)
	{
		sceneManager();
	}


	return 0;
}