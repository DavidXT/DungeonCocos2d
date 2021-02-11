#pragma once
#include "Enemy.h"

class Room
{
	int posX;
	int posY;
	int treasurePosX;
	int treasurePosY;
	bool haveChest = true;
	bool haveE1 = true;
	bool haveE2 = true;
	Enemy* E1;
	Enemy* E2;

public:
	Room(int x, int y);
	void TakeChest();
	void killE1();
	void killE2();
	Enemy* getEnemy1() { return E1; };
	Enemy* getEnemy2() { return E2; };
	bool getHaveE1() { return haveE1; };
	bool getHaveE2() { return haveE2; };
	bool getTreasure() { return haveChest; };
	int getTreasurePosX() {return treasurePosX;};
	int getTreasurePosY() {return treasurePosY;};
	int getX() { return posX; }
	int getY() { return posY; }
};
