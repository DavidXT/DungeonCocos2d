#pragma once
#include <string>
class Enemy
{
	std::string sprite;
	int roomPosX;
	int roomPosY;

protected:
	Enemy(std::string sprite, int x, int y);
	std::string GetSprite();
	void SetSprite(std::string newSprite);
	int GetPosX();
	int GetPosY();

};

