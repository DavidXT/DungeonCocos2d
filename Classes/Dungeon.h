#pragma once
#include <vector>
#include "Room.h"

class Dungeon
{
	int sizeX;
	int sizeY;
	int winX;
	int winY;
public:
	Dungeon(int,int, int); //Constructor
	std::vector<std::vector<Room*>> AllRoom; //Array of room
	//Getter
	Room* getRoom(int, int);
	int getSizeX() { return sizeX; };
	int getSizeY() { return sizeY; };
	int getWinX() { return winX; };
	int getWinY() { return winY; };
};

