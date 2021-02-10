#include "Enemy.h"
#include "EntryPoint.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
const int ScreenWidth = 1024;
const int ScreenHeight = 768;

Enemy::Enemy()
{
	roomPosX = rand() % (ScreenWidth / 2 + 200) + 100;
	roomPosY = rand() % (ScreenHeight / 2) + 200;
	sprite = (rand() % 5);
}

/// <summary>
/// Get enemy sprite name
/// </summary>
/// <returns> Enemy sprite name </returns>
int Enemy::GetSprite()
{
	return sprite;
}

/// <summary>
/// Set enemy sprite name
/// </summary>
/// <param name="newSprite"> New sprite name</param>
void Enemy::SetSprite(int newSprite)
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
