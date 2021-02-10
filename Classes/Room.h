#pragma once
#include "Enemy.h"

class Room
{
	int posX;
	int posY;
	int treasurePosX;
	int treasurePosY;
	bool haveChest;
	Enemy* E1;
	Enemy* E2;

public:
	Room(int x, int y);
	void TakeChest();
	Enemy* getEnemy1() { return E1; };
	Enemy* getEnemy2() { return E2; };
	int getTreasurePosX() {return treasurePosX;};
	int getTreasurePosY() {return treasurePosY;};
};
