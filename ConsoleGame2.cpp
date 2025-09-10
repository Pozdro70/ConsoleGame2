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
		//remove_scrollbar();
	#endif
	/* FASTER PRINTING
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	*/

	_getch(); // Pause before start
	
	
	MapManager mapManager;
	GameMap gmap;
	gmap=mapManager.generateMap(time(nullptr),"Game1", "Game1.msave", "InDev-0.1", 10, 10);
	
	mapManager.putMapOnScreen(gmap);


	//mapManager.saveGameMap(gmap);
	/*
	GameMap gmap2;
	gmap2 =mapManager.loadMapFromFile("Game1.msave");

	for (int x = 0; x < gmap2.sizeX; x++) {
		for (int y = 0; y < gmap2.sizeY; y++) {
			setCursorPos(x, y); std::cout << gmap2.mapImage[x][y].id;
		}
	}
	*/
	//dispAllRooms();
	return 0;

	

}

