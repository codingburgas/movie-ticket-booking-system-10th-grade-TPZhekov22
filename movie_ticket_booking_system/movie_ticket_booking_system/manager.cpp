#include "manager.h"
#include "menus.h"
#include "../system_static_library/namespaceUtility.h"

void sceneManager()
{
	while (utility::exit == false)
	{
		mainMenu();
	}
}