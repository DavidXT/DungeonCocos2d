#pragma once
class Room
{
	int posX;
	int posY;
	bool haveChest;

protected:
	Room(int x, int y);
	void TakeChest();
};

