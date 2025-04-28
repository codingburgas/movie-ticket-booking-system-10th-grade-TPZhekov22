#include "manager.h"
#include "../system_static_library/namespaceUtility.h"

int main()
{
	while (utility::exit == false)
	{
		sceneManager();
	}
	
	return 0;
}