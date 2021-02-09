#pragma once

class Room;

class Dungeon
{
	std::vector<std::vector<Room*>> AllRoom;
public:
	Dungeon(int, int);
};


