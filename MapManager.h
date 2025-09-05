#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

//Typ pomieszczenia
enum RoomType {
	IRoom=1,
	TRoom=2,
	LRoom=3,
	endRoom=4,
	XRoom=5,
	SpecialRoom=6
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
		std::string specialRoomLine;

		for (Room &room : rFiles)
		{
			std::ifstream roomFile(mainFilePath+room.fname);
			getline(roomFile, roomline);
			std::stringstream roomHeaderLine1(roomline);
			getline(roomHeaderLine1, specialRoomLine, ':');
			getline(roomHeaderLine1, specialRoomLine, ':');
			room.name = specialRoomLine;
			
			getline(roomFile, roomline);
			std::stringstream roomHeaderLine2(roomline);
			getline(roomHeaderLine2, specialRoomLine, ':');
			getline(roomHeaderLine2, specialRoomLine, ':');
			room.roomType = static_cast<RoomType>(std::atoi(specialRoomLine.c_str()));

			getline(roomFile, roomline);
			std::stringstream roomHeaderLine3(roomline);
			getline(roomHeaderLine3, specialRoomLine, ':');
			getline(roomHeaderLine3, specialRoomLine, ':');
			room.passages = std::atoi(specialRoomLine.c_str());

			getline(roomFile, roomline);
			inRoomSection = true;
			while (getline(roomFile, roomline)) {
				if (roomline == "roomend;") {
					inRoomSection = false;
					continue;
				}
				room.roomImage.emplace_back(roomline);
			}
			roomFile.close();
			
			
		}

		return rFiles;
		
	}
};