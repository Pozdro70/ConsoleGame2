#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include "MapManager.h"
#include <vector>
#include <ctime>



int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8); // Windows UTF-8 console
#endif

	//dispAllRooms();
	MapManager mapManager;
	mapManager.generateMap(time(nullptr));

}

