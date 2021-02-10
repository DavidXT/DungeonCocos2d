#pragma once
#include <vector>
#include "Room.h"

class Dungeon
{
	int sizeX;
	int sizeY;
public:
	Dungeon(int,int, int);
	Room* getRoom(int, int);
	std::vector<std::vector<Room*>> AllRoom;
	int getSizeX() { return sizeX; };
	int getSizeY() { return sizeY; };
};

