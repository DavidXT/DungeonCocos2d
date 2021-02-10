#include "Player.h"
#include "EntryPoint.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;
Player::Player(int coordX, int coordY) {
	X = coordX;
	Y = coordY;
	gold = 0;
}
void Player::AddGold(int x) {
	gold += x;
}
void Player::moveDown() {
	Y--;
}
void Player::moveUp() {
	Y++;
}
void Player::moveLeft()
{
	X--;
}
void Player::moveRight() {
	X++;
}
int Player::getPosX() {
	return X;
}
int Player::getPosY() {
	return Y;
}

int Player::getGold() {
	return gold;
}