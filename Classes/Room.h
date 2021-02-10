#pragma once
class Room
{
	int posX;
	int posY;
	bool haveChest;

public:
	Room(int x, int y);
	void TakeChest();
};
