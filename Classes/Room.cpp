#include "Room.h"
#include "EntryPoint.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

const int ScreenWidth = 1024;
const int ScreenHeight = 768;

Room::Room(int x, int y)
{
	posX = x;
	posY = y;
	E1 = new Enemy();
	E2 = new Enemy();
	treasurePosX = rand() % (ScreenWidth / 2 + 200) + 100;
	treasurePosY = rand() % (ScreenHeight / 2) + 200;
}

/// <summary>
/// Take chest in the room
/// </summary>
void Room::TakeChest()
{
	haveChest = false;
}