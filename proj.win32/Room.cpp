#include "Room.h"

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