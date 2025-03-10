#include "manager.h"

int main()
{


	while (!Scene.currentScene == EXIT)
	{

		BeginDrawing();


		sceneManager();

		
		EndDrawing();
	}


	
	CloseWindow();
	return 0;
}