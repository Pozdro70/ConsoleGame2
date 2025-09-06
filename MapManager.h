#include "RoomManager.h"
#include <iostream>
#include <random>
#include "ConsoleUtils.h"

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
	void placeRoom(Room room,int x,int y) {
		int starty=y;
		for (std::string i : room.roomImage) {
			setCursorPos(x, starty); std::cout << i;
			starty++;
		}
	}

public:
	void generateMap(int mapseed) {
		// Inicjalizacja generatora liczb losowych z podanym seedem
		std::mt19937 randomGen(mapseed);
		
		//Wczytywanie pomieszczen
		RoomManager roomManager;
		std::vector<Room> rooms;
		rooms = roomManager.loadMapRooms();

		//Stawianie pomieszczenia startowego

		for (Room room : rooms) {
			if (room.roomType == RoomType::endRoom && room.exitRotations.front() == RoomExitRotation::East && room.passages==1) {
				placeRoom(room, 0, getConsoleHeight()/2);
			}
		}
	}
};

