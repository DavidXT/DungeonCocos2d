#include "Enemy.h"

Enemy::Enemy(std::string newSprite, int x, int y)
{
	roomPosX = x;
	roomPosY = y;
	sprite = newSprite;
}

/// <summary>
/// Get enemy sprite name
/// </summary>
/// <returns> Enemy sprite name </returns>
std::string Enemy::GetSprite()
{
	return sprite;
}

/// <summary>
/// Set enemy sprite name
/// </summary>
/// <param name="newSprite"> New sprite name</param>
void Enemy::SetSprite(std::string newSprite)
{
	sprite = newSprite;
}

/// <summary>
/// Get enemy position in room for X axis
/// </summary>
/// <returns> Enemy in room poistion for X axis </returns>
int Enemy::GetPosX()
{
	return roomPosX;
}


/// <summary>
/// Get enemy position in room for Y axis
/// </summary>
/// <returns> Enemy in room poistion for Y axis </returns>
int Enemy::GetPosY()
{
	return roomPosY;
}
