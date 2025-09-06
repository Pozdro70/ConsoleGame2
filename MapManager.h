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
	std::vector<int> entranceOffset;
};


//Glowna klasa MapManager
#pragma once
class MapManager
{
	//Sciezki do plikow
	std::string mapManagerVersion = "1.0";
	std::string mainRoomsFilePath = "GameData/MapGen/rooms.mrooms";
	std::string mainFilePath = "GameData/MapGen/";

	std::vector<Room> loadMapRoomFiles() {
		//Wczytywanie pliku z glowna lista pomieszczen
		std::ifstream roomsHeaderFile(mainRoomsFilePath);
		
		std::string line;
		bool inRoomsSection = false;
		std::vector<Room> roomsFiles;
		//przetwazanie pliku z glowna lista pomieszczen
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
				//wczytywanie nazw plików z pomieszczeniami i ich ID do vectora
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

		//Zamkniecie pliku z glowna lista pomieszczen
		roomsHeaderFile.close();
		return roomsFiles;
	}

	//Funkcja wczytujaca wszystkie pomieszczenia z plikow do vectora
public:
	std::vector<Room> loadMapRooms()
	{
		//pobieranie listy plikow z pomieszczeniami
		std::vector<Room> rFiles;
		rFiles=loadMapRoomFiles();
		
		//Zmiennne pomocnicze do przetwarzania plikow z pomieszczeniami
		bool inRoomSection = false;
		bool inRotSection=false;
		bool inExitOSection = false;
		std::string roomline;
		std::string specialRoomLine;

		//Wczytywanie kazdego pliku z pomieszczeniem i przetwarzanie jego zawartosci
		for (Room &room : rFiles)
		{
			//otwieranie pliku z pomieszczeniem
			std::ifstream roomFile(mainFilePath+room.fname);

			//wczytywanie nazwy pomieszczenia
			getline(roomFile, roomline);
			std::stringstream roomHeaderLine1(roomline);
			getline(roomHeaderLine1, specialRoomLine, ':');
			getline(roomHeaderLine1, specialRoomLine, ':');
			room.name = specialRoomLine;

			//wczytywanie typu pomieszczenia
			getline(roomFile, roomline);
			std::stringstream roomHeaderLine2(roomline);
			getline(roomHeaderLine2, specialRoomLine, ':');
			getline(roomHeaderLine2, specialRoomLine, ':');
			room.roomType = static_cast<RoomType>(std::atoi(specialRoomLine.c_str()));

			//wczytywanie liczby wyjsc z pomieszczenia
			getline(roomFile, roomline);
			std::stringstream roomHeaderLine3(roomline);
			getline(roomHeaderLine3, specialRoomLine, ':');
			getline(roomHeaderLine3, specialRoomLine, ':');
			room.passages = std::atoi(specialRoomLine.c_str());

			//wczytywanie rotacji wyjsc z pomieszczenia
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
			
			//wczytywanie offsetow wyjsc i wejsc z pomieszczenia
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

				//wczytywanie offsetu wejscia do pomieszczenia
				getline(roomFile, roomline);

				std::stringstream roomlineInOffsetSs(roomline);
				std::string roominoffsetcord;
				std::string roominoffset;

				getline(roomlineInOffsetSs, roominoffsetcord, ':');
				getline(roomlineInOffsetSs, roominoffsetcord, ':');

				std::stringstream roomlineInOffsetSsCord(roominoffsetcord);
				getline(roomlineInOffsetSsCord, roominoffset, ';');

				room.entranceOffset.emplace_back(atoi(roominoffset.c_str()));
				getline(roomlineInOffsetSsCord, roominoffset, ';');
				room.entranceOffset.emplace_back(atoi(roominoffset.c_str()));

				//wczytywanie grafiki pomieszczenia
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

