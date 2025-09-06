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

//Rotacja wyjscia pomieszczenia patrzac od gory
enum RoomExitRotation {
	North=1,
	East=2,
	South=3,
	West=4
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
	std::vector<RoomExitRotation> exitRotations;
	std::vector<std::vector<int>> exitOffsets;
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
		bool inRotSection=false;
		bool inExitOSection = false;
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
			if (roomline == "exitrot:") {
				inRotSection = true;
			}
			
			
			while (inRotSection) {
				getline(roomFile, roomline);

				if (roomline == "endrot;") {
					inRotSection = false;
					continue;
				}
				room.exitRotations.emplace_back(static_cast<RoomExitRotation>(std::atoi(roomline.c_str())));
				
			}
			

			if (!inRotSection) {
				
				getline(roomFile, roomline);
				if (roomline == "exitsoffset:") { inExitOSection = true; }

				if (inExitOSection) {
					while (inExitOSection) {
						getline(roomFile, roomline);
						if (roomline == "endexitoffset;") { inExitOSection = false; continue; }
						std::stringstream roomlineSs(roomline);
						std::string roomlinesegment;
						std::vector<int> temp = {0,0};

						getline(roomlineSs, roomlinesegment, ';');
						temp[0]= atoi(roomlinesegment.c_str());
						
						getline(roomlineSs, roomlinesegment, ';');
						temp[1] = atoi(roomlinesegment.c_str());

						room.exitOffsets.emplace_back(temp);
					}
				}

				getline(roomFile, roomline);
				if (roomline == "room:") { inRoomSection = true; }
				if (inRoomSection)
				{
					while (getline(roomFile, roomline))
					{
						if (roomline == "roomend;")
						{
							inRoomSection = false;
							continue;
						}
						room.roomImage.emplace_back(roomline);
					}
				}
			}
			roomFile.close();
			
		}

		return rFiles;
		
	}
};

