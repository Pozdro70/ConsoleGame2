#ifdef _WIN32
#include <windows.h>
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
	mapManager.generateMap(time(nullptr));
	//dispAllRooms();
	return 0;

	

}

