#include "RoomManager.h"
#include <iostream>
#include <random>

//funkcja debugujaca wyswietlajaca wszystkie wczytane pomieszczenia
static void dispAllRooms() {
	//debug code to show all rooms
	RoomManager roomManager;
	std::vector<Room> rooms;
	rooms = roomManager.loadMapRooms();
	for (Room j : rooms) {
		std::cout << "\n" << j.name << "\n";
		for (std::string i : j.roomImage) {
			std::cout << i << "\n";
		}
	}
}

#pragma once
class MapManager
{
public:
	void generateMap(int mapseed) {
		// Inicjalizacja generatora liczb losowych z podanym seedem
		std::mt19937 randomGen(mapseed);

		
	}
};

