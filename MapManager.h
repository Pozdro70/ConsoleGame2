#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

//Typ pomieszczenia
enum RoomType {
	IRoom,
	TRoom,
	LRoom,
	endRoom,
	XRoom,
	SpecialRoom
};

//Klasa pomieszczenia
class Room {
public:
	int id;
	std::string name;
	std::string fname;
	RoomType roomType;
	int passages;
	std::vector<std::string> roomImage;
};


//Glowna klasa MapManager
#pragma once
class MapManager
{
	std::string mapManagerVersion = "1.0";
	std::string mainRoomsFilePath = "GameData/MapGen/rooms.mrooms";
	std::string mainFilePath = "GameData/MapGen/";
	std::vector<Room> loadMapRoomFiles() {
		std::ifstream roomsHeaderFile(mainRoomsFilePath);

		std::string line;
		bool inRoomsSection = false;
		std::vector<Room> roomsFiles;

		while(getline(roomsHeaderFile, line)) {
			
			
			if (line == "rooms:") {
				inRoomsSection = true;
				continue;
			}
			if (line == "endrooms") {
				inRoomsSection = false;
				continue;
			}

			
			if (inRoomsSection) {

				std::stringstream roomHeaderFLine(line);
				std::string roomFileName;
				int roomID;
				std::string segment;

				getline(roomHeaderFLine, segment, '-');
				roomID = std::atoi(segment.c_str());
				getline(roomHeaderFLine, segment,'-');
				roomFileName = segment;
				
				Room toReturn;
				toReturn.id = roomID;
				roomFileName.erase(roomFileName.end() - 1);
				toReturn.fname = roomFileName;

				roomsFiles.emplace_back(toReturn);
			}
			
		}

		roomsHeaderFile.close();
		return roomsFiles;
	}

public:
	std::vector<Room> loadMapRooms()
	{

		
		std::vector<Room> rFiles;
		rFiles=loadMapRoomFiles();

		bool inRoomSection = false;
		std::string roomline;
		for (Room &room : rFiles)
		{
			std::ifstream roomFile(mainFilePath.append(room.fname));
			getline(roomFile, roomline);
			getline(roomFile, roomline);
			getline(roomFile, roomline);
			getline(roomFile, roomline);
			inRoomSection = true;
			while (getline(roomFile, roomline)) {
				if (roomline == "roomend;") {
					inRoomSection = false;
					continue;
				}
				room.roomImage.emplace_back(roomline);
			}

			
		}

		return rFiles;
		
	}
};