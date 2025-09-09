#ifdef _WIN32
#include <windows.h>
#include "ConsoleUtils.h"
#endif
#include <iostream>
#include "MapManager.h"
#include <vector>
#include <ctime>
#include <conio.h>




int main()
{
	#ifdef _WIN32
		SetConsoleOutputCP(CP_UTF8); // Windows UTF-8 console
	#endif
	

	_getch(); // Pause before start
	
	
	MapManager mapManager;
	GameMap gmap;
	gmap=mapManager.generateMap(time(nullptr),"Game1", "Game1.msave", "InDev-0.1", 10, 10);
	
	for (int x = 0; x < gmap.sizeX; x++) {
		for (int y = 0; y < gmap.sizeY; y++) {
			setCursorPos(x, y); std::cout << gmap.mapImage[x][y].id;
		}
	}

	mapManager.saveGameMap(gmap);

	//dispAllRooms();
	return 0;

	

}

