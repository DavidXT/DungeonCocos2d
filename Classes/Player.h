#pragma once
class Player
{
	int X ;
	int Y;
	int gold ;
public:
	Player(int, int); //Constructor
	void AddGold(int);
	//Function of movement
	void moveDown();
	void moveUp();
	void moveLeft();
	void moveRight();
	//Getter
	int getPosX();
	int getPosY();
	int getGold();
};


