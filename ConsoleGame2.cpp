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
	

	//debug code to show all rooms

	MapManager mapManager;
	std::vector<Room> rooms;
	rooms=mapManager.loadMapRooms();
	for (Room j : rooms) {
		for (std::string i : j.roomImage) {
			std::cout << i << "\n";
		}
	}
	
	
}
