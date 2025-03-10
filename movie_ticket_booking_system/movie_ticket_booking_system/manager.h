#pragma once

void sceneManager();

// Structure to manage scenes
struct SCENE
{
	enum Scene {EXIT, MENU};
	Scene currentScene = MENU;
};

extern SCENE scene;