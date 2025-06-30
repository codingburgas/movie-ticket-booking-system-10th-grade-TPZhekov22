#include "manager.h"
#include "accountSignIn.h"
#include "menus.h"
#include "../system_static_library/namespaceUtility.h"

void sceneManager()
{
	Account currentAccount = accountSignIn();
	while (utility::exit == false)
	{
		mainMenu(currentAccount);
	}
}