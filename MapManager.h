#include "RoomManager.h"
#include <iostream>
#include <random>
#include "ConsoleUtils.h"
#include <iostream>
#include <fstream>  
#include <vector>
#include <string>
#include <stack>

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

class Map {
public:
	std::string saveName;
	std::string gameVersion;
	std::vector<std::vector<char>> mapImage;
	int sizeX;
	int sizeY;
};

class MapRoomCell {
	bool visited;
	Room room;
	RoomType roomType;
};

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

		/*
		//Stawianie pomieszczenia startowego

		for (Room room : rooms) {
			if (room.roomType == RoomType::endRoom && room.exitRotations.front() == RoomExitRotation::East && room.passages==1) {
				placeRoom(room, 0, getConsoleHeight()/3);
			}
		}
		*/

		//Inicjalizacja mapy
		std::vector<std::string> mapFile;
		Map map;

		map.saveName = "NewMap1"; // TODO: naming not implemented yet
		map.gameVersion = "0.0.1-InDev"; // TODO: versioning not implemented yet
		map.sizeX = 100;
		map.sizeY = 100;


		std::vector<std::vector<MapRoomCell>> mapCells;
		std::stack<MapRoomCell> visitedMapCells;
		
	}
};

