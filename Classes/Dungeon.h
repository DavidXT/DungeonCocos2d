#pragma once
#include <vector>
#include "Room.h"

class Dungeon
{

public:
	Dungeon(int,int, int);
	Room* getRoom(int, int);
	std::vector<std::vector<Room*>> AllRoom;
};

