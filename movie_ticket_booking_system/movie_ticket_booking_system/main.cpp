#include "manager.h"
#include "createNewObjects.h"
#include "loadObjectData.h"

int main()
{
	//sceneManager();
	std::vector<City> cities = loadCitiesFromFile();
	for (const auto& city : cities)
	{
		std::cout << "City: " << city.getCityName() << '\n';
		city.displayCinemas();
	}

	return 0;
}
