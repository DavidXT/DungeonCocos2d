#pragma once
#include <string>
class Enemy
{
	int sprite;
	int roomPosX;
	int roomPosY;

public:
	Enemy();
	int GetSprite();
	void SetSprite(int);
	int GetPosX();
	int GetPosY();

};

