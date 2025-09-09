#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "RoomManager.h"
#include <iostream>
#include <random>
#include "ConsoleUtils.h"
#include <iostream>
#include <fstream>  
#include <vector>
#include <string>
#include <stack>
#include <conio.h>

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

class GameMap {
public:
	std::string saveName;
	std::string gameVersion;
	std::vector<std::vector<Room>> mapImage;
	int sizeX;
	int sizeY;
};

class MapRoomCell {
public:
	bool visited;
	Room room;
	RoomType roomType;
	int posX;
	int posY;
	int lastlyChosenSide;
	int howManyPassages=0;
	std::vector<int> exitRotations;
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
	GameMap generateMap(int mapseed) {
		// Inicjalizacja generatora liczb losowych z podanym seedem
		std::mt19937 randomGen(mapseed);
		std::uniform_int_distribution<int> randomSideDist(1, 4); // Dystrybucja do losowania strony (1-4)
		
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
		GameMap map;

		map.saveName = "NewMap1"; // TODO: naming not implemented yet
		map.gameVersion = "0.0.1-InDev"; // TODO: versioning not implemented yet
		map.sizeX = 100;
		map.sizeY = 100;
		
		
		for (int i = 0; i < map.sizeX; i++) {
			map.mapImage.emplace_back(std::vector<Room>());
			for (int j = 0; j < map.sizeY; j++) {

				map.mapImage[i].emplace_back(Room{});
			}
		}
		
		

		MapRoomCell defaultCell;
		defaultCell.visited = false;

		std::vector<std::vector<MapRoomCell>> mapCells(map.sizeX,std::vector<MapRoomCell>(map.sizeY, defaultCell));
		std::stack<MapRoomCell*> visitedMapCells;

		int currentX = 0;
		int currentY = 0;

		/*
		for (std::vector<MapRoomCell> mapCellX : mapCells) {
			for (MapRoomCell mapCellY :mapCellX) {
				mapCellY.visited = false;
			}
		}
		*/
		

		visitedMapCells.push(&mapCells[0][0]);
		mapCells[0][0].visited = true;
		bool hasChanged=false;

		int stepCount = 0;
		std::vector<int> directionsTried;

		while (!visitedMapCells.empty()) {
			int randomSide = randomSideDist(randomGen); //losowanie strony z ktorej bedzie wyjscie z pomieszczenia startowego
			hasChanged=false;
			//std::cout << "Random side: " << randomSide << "\n";
			

			if (randomSide == 1 && (!hasChanged && !std::count(directionsTried.begin(), directionsTried.end(), 1))) {
				
				if (currentX < map.sizeX && currentY+1 < map.sizeY && currentX >=0 && currentY+1 >=0) {
					//std::cout << "Checking cell: " << currentX << "," << currentY + 1 << "\n";
					if (mapCells[currentX][currentY + 1].visited == false) {
						currentY++;
						hasChanged = true; directionsTried.clear();
						//std::cout << "Moved to cell: " << currentX << "," << currentY << "\n";
					}
				}
			}
			else if (randomSide == 2 && (!hasChanged && !std::count(directionsTried.begin(), directionsTried.end(), 2))) {
				if (currentX+1 < map.sizeX && currentY < map.sizeY && currentX+1 >=0 && currentY >=0) {
					//std::cout << "Checking cell: " << currentX + 1 << "," << currentY << "\n";
					if (mapCells[currentX+1][currentY].visited == false) {
						currentX++;
						hasChanged = true; directionsTried.clear();
						//std::cout << "Moved to cell: " << currentX << "," << currentY << "\n";
					}
				}
			}
			else if (randomSide == 3 && (!hasChanged && !std::count(directionsTried.begin(), directionsTried.end(), 3))) {
				if (currentX < map.sizeX && currentY - 1 < map.sizeY && currentX >=0 && currentY - 1 >= 0) {
					//std::cout << "Checking cell: " << currentX << "," << currentY - 1 << "\n";
					if (mapCells[currentX][currentY-1].visited == false) {
						currentY--;
						hasChanged = true; directionsTried.clear();
						//std::cout << "Moved to cell: " << currentX << "," << currentY << "\n";
					}
				}
			}
			else if (randomSide == 4 && (!hasChanged && !std::count(directionsTried.begin(), directionsTried.end(), 4))) {
				if (currentX-1 < map.sizeX && currentY < map.sizeY && currentX-1 >=0 && currentY >=0) {
					//std::cout << "Checking cell: " << currentX - 1 << "," << currentY << "\n";
					if (mapCells[currentX-1][currentY].visited == false) {
						currentX--;
						hasChanged = true; directionsTried.clear();
						//std::cout << "Moved to cell: " << currentX << "," << currentY << "\n";
					}
				}
			}
			directionsTried.emplace_back(randomSide);
			if (
				   std::count(directionsTried.begin(), directionsTried.end(), 1)
				&& std::count(directionsTried.begin(), directionsTried.end(), 2)
				&& std::count(directionsTried.begin(), directionsTried.end(), 3)
				&& std::count(directionsTried.begin(), directionsTried.end(), 4)
				) {
				
					if (visitedMapCells.size()>1) {
						
						visitedMapCells.pop();
						
						currentX = visitedMapCells.top()->posX;
						currentY = visitedMapCells.top()->posY;

						//std::cout << "Backtracking to cell: " << currentX << "," << currentY << "\n";
						directionsTried.clear();
						directionsTried.emplace_back(mapCells[currentX][currentY].lastlyChosenSide);
						
						
					}
					else
					{
						break;
					}
			}

			if (hasChanged) {
				mapCells[currentX][currentY].visited = true;
				visitedMapCells.push(&mapCells[currentX][currentY]);
				mapCells[currentX][currentY].posX = currentX;
				mapCells[currentX][currentY].posY = currentY;
				//std::cout << "Visiting cell: " << currentX << "," << currentY << "\n";
				mapCells[currentX][currentY].lastlyChosenSide = randomSide;
				mapCells[currentX][currentY].howManyPassages++;
				mapCells[currentX][currentY].exitRotations.emplace_back(randomSide);
				stepCount++;
				directionsTried.clear();
				
			}
		}
		
		
		clearConsole();

		int foundRoomsRotCounter = 0;
		for (int x = 0; x < map.sizeX; x++) {
			for (int y = 0; y < map.sizeY; y++) {
				if (!mapCells[x][y].exitRotations.empty()) {
					
					
					for (int i : mapCells[x][y].exitRotations) {
						for (Room roomi : rooms) {
							bool allMatch = true;
							for (int requiredExit : mapCells[x][y].exitRotations) {
								if (std::find(roomi.exitRotations.begin(), roomi.exitRotations.end(), requiredExit) == roomi.exitRotations.end()) {
									allMatch = false;
									break;
								}
							}

							if (allMatch) {
								mapCells[x][y].room = roomi;
								break;
							}
						}
						
					}
					
				}
			}

		}
		

		for (int x = 0; x < map.sizeX; x++) {
			for (int y = 0; y < map.sizeY; y++) {
				if (!mapCells[x][y].exitRotations.empty()) {
					map.mapImage[x][y] = mapCells[x][y].room;
				}
			}
		}

		return map;
		
		
	}
};

