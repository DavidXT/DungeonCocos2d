#include "Room.h"
#include "EntryPoint.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

Room::Room(int x, int y)
{
	posX = x;
	posY = y;
}

/// <summary>
/// Take chest in the room
/// </summary>
void Room::TakeChest()
{
	haveChest = false;
}