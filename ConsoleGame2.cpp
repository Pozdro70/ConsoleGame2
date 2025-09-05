#include <iostream>
#include "MapManager.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <vector>

int main()
{
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8); // Windows UTF-8 console
	#endif
	
	MapManager mapManager;
	std::vector<Room> rooms;
	rooms=mapManager.loadMapRooms();
	for (std::string i :rooms[1].roomImage) {
		std::cout << i<<"\n";
	}
	
}
