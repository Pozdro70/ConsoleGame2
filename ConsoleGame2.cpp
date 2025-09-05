#include <iostream>
#include "MapManager.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <vector>

void dispAllRooms() {
	//debug code to show all rooms
	MapManager mapManager;
	std::vector<Room> rooms;
	rooms = mapManager.loadMapRooms();
	for (Room j : rooms) {
		std::cout << "\n" << j.name << "\n";
		for (std::string i : j.roomImage) {
			std::cout << i << "\n";
		}
	}
}


int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8); // Windows UTF-8 console
#endif

	dispAllRooms();
}

