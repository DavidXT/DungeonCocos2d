#pragma once
class Player
{
	int X ;
	int Y;
	int gold ;
public:
	Player(int, int);
	void AddGold(int);
	void moveDown();
	void moveUp();
	void moveLeft();
	void moveRight();
	int getPosX();
	int getPosY();
	int getGold();
};


