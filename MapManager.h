#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
};


//Glowna klasa MapManager
#pragma once
class MapManager
{
public:
	void loadMapRoomFiles() {
		
	}
};