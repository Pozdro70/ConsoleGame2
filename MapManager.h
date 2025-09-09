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
	std::string saveFileName;
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
	GameMap generateMap(int mapseed, std::string saveNameinp,std::string saveFileNameinp, std::string gameVersioninp, int sizeXinp, int sizeYinp) {
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

		map.saveName = saveNameinp; // TODO: naming not implemented yet
		map.saveFileName = saveFileNameinp;
		map.gameVersion = gameVersioninp; // TODO: versioning not implemented yet
		map.sizeX = sizeXinp;
		map.sizeY = sizeYinp;
		
		
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

	void saveGameMap(GameMap gmap) {
		std::ofstream saveFile("GameData/Saves/" + gmap.saveFileName);

		saveFile << "ver:1.0\n";
		saveFile << "savename:"+gmap.saveName+"\n";
		saveFile << "gamever:"+gmap.gameVersion+"\n";
		saveFile << "sizex:"+std::to_string(gmap.sizeX)+"\n";
		saveFile << "sizey:"+ std::to_string(gmap.sizeY)+"\n";
		saveFile << "map:\n";
		for (int x = 0; x < gmap.sizeX; x++) {
			for (int y = 0; y < gmap.sizeY; y++) {
				saveFile << gmap.mapImage[y][x].id<<";";
			}
			saveFile << "\n";
		}
		saveFile << "endmap;";

	
		
		saveFile.close();
	}

	GameMap loadMapFromFile(std::string path) {

		std::ifstream mapFile("GameData/Saves/" + path);
		if (!mapFile.is_open()) {
			std::cerr << "Failed to open map file: " << path << "\n";
			return GameMap{};
		}

		GameMap gmap;
		std::string line;

		// --- Read header ---
		getline(mapFile, line); // ver (skip)

		getline(mapFile, line); // savename
		gmap.saveName = line.substr(line.find(':') + 1);
		gmap.saveFileName = gmap.saveName + ".msave";

		getline(mapFile, line); // gamever
		gmap.gameVersion = line.substr(line.find(':') + 1);

		getline(mapFile, line); // sizex
		gmap.sizeX = std::stoi(line.substr(line.find(':') + 1));

		getline(mapFile, line); // sizey
		gmap.sizeY = std::stoi(line.substr(line.find(':') + 1));

		// --- Initialize map containers ---
		gmap.mapImage.resize(gmap.sizeX, std::vector<Room>(gmap.sizeY));
		std::vector<std::vector<int>> mapImageIDs(gmap.sizeX, std::vector<int>(gmap.sizeY, 0));

		// --- Read map section ---
		getline(mapFile, line); // should be "map:"
		if (line != "map:") {
			std::cerr << "Invalid map format in file: " << path << "\n";
			return gmap;
		}

		RoomManager roomManager;
		int y = 0;
		while (getline(mapFile, line) && line != "endmap;") {
			std::stringstream lineSS(line);
			std::string segment;
			int x = 0;

			while (getline(lineSS, segment, ';')) {
				if (segment.empty()) continue; // skip trailing ;
				if (x < gmap.sizeX && y < gmap.sizeY) {
					mapImageIDs[x][y] = std::stoi(segment);
				}
				x++;
			}
			y++;
		}

		mapFile.close();

		// --- Convert IDs to Rooms ---
		for (int x = 0; x < gmap.sizeX; x++) {
			for (int y = 0; y < gmap.sizeY; y++) {
				gmap.mapImage[x][y] = roomManager.getRoomByID(mapImageIDs[x][y], roomManager.loadMapRooms());
			}
		}

		return gmap;
	}

};

