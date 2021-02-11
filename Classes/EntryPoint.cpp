#include "EntryPoint.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "Dungeon.h"
#include <time.h>

USING_NS_CC;
using namespace CocosDenshion;

std::vector<std::string> enemiesSprites;
int enemyCount;
std::string tempName;


const std::string DEFAULT_FONT = "fonts/Arial.ttf";
const int ScreenWidth = 1024;
const int ScreenHeight = 768;
Dungeon* dungeon;
Player* player;

void EntryPoint::Init(Node *parent)
{
	srand(time(NULL));
	enemiesSprites.push_back("mob_1.png");
	enemiesSprites.push_back("mob_2.png");
	enemiesSprites.push_back("mob_3.png");
	enemiesSprites.push_back("mob_4.png");
	enemiesSprites.push_back("mob_5.png");


	_parent = parent;
	_background = Sprite::create("background.png");
	_background->setPosition(ScreenWidth / 2, ScreenHeight / 2);
	_background->setScale(1, 1);
	_parent->addChild(_background);

	// labels
	_gold_label = Label::createWithTTF("Player gold : 0", DEFAULT_FONT, 24);
	_gold_label->setPosition(100, 100);

	_time_label = Label::createWithTTF("", DEFAULT_FONT, 24);
	_time_label->setPosition(0, 0);
	_time_label->setAnchorPoint(Vec2(0, 0));

	_parent->addChild(_gold_label);
	_parent->addChild(_time_label);

	//Génération du donjon
	dungeon = new Dungeon(10,10,7);
	player = new Player(dungeon->getSizeX() / 2, dungeon->getSizeY() / 2);
	//Génération des portes au début du donjon
	_AddDoorDown();
	_AddDoorUp();
	_AddDoorLeft();
	_AddDoorRight();
	_updateDoor();
	Room* actualRoom = dungeon->getRoom(player->getPosX(), player->getPosY());
	_AddTreasure();
	_SpawnEnemy();
	SpawnPlayer();
	_DrawMap();
}

void EntryPoint::_AddTreasure()
{
	Room* actualRoom = dungeon->getRoom(player->getPosX(), player->getPosY());
	_treasure = Sprite::create("chest_closed.png");
	_treasure->setPosition(actualRoom->getTreasurePosX(), actualRoom->getTreasurePosY());
	_treasure->setScale(2,2);
	//_treasure->setScale((rand() % 30) / 10.0f + 2.0f);
	_parent->addChild(_treasure);
}

void EntryPoint::ClearRoom()
{
	if (_enemy != nullptr) {
		_enemy->removeFromParent();
		_enemy = nullptr;
	}
	if (_enemy2 != nullptr) {
		_enemy2->removeFromParent();
		_enemy2 = nullptr;
	}
	_player->removeFromParent();
	_player = nullptr;

	if (_treasure != nullptr)
	{
		_treasure->removeFromParent();
		_treasure = nullptr;
	}
}

void EntryPoint::EnterRoom()
{
	Room* actualRoom = dungeon->getRoom(player->getPosX(), player->getPosY());
	_updateDoor();
	if (actualRoom->getTreasure()) {
		_AddTreasure();
	}
	_SpawnEnemy();
	_updateMap();
}

void EntryPoint::_updateDoor() {
	if (player->getPosX() < dungeon->getSizeX() && dungeon->AllRoom[player->getPosX() + 1][player->getPosY()] != nullptr) _doorRight->setVisible(true);
	else _doorRight->setVisible(false);

	if (player->getPosX() > 0 && dungeon->AllRoom[player->getPosX() - 1][player->getPosY()] != nullptr) _doorLeft->setVisible(true);
	else _doorLeft->setVisible(false);

	if (player->getPosY() > 0 && dungeon->AllRoom[player->getPosX()][player->getPosY() - 1] != nullptr) _doorDown->setVisible(true);
	else _doorDown->setVisible(false);

	if (player->getPosY() < dungeon->getSizeY() && dungeon->AllRoom[player->getPosX()][player->getPosY() +1] != nullptr) _doorUp->setVisible(true);
	else _doorUp->setVisible(false);
}

void EntryPoint::_DrawMap()
{
	//add map button
	_mapButton = Sprite::create("paper_scroll.png");
	_mapButton->setPosition(ScreenWidth / 25, ScreenHeight / 20 * 19);
	_mapButton->setScale(0.12,0.16);
	_parent->addChild(_mapButton);

	//map sprite
	_map = Sprite::create("paper_scroll.png");
	_map->setPosition(ScreenWidth / 2, ScreenHeight / 2);
	_map->setScale(2, 2);
	_parent->addChild(_map);

	//get size of room sprite
	_room = Sprite::create("room.png");
	Size size = _room->getContentSize();
	float roomWidth = size.width;
	float roomHeight = size.height;

	//go through dungeon room
	int i = 0;
	for (std::vector<Room*> line : dungeon->AllRoom) {
		for (Room* r : line) {

			if (r != nullptr) {//room exist, add sprite

				log("%d , %d", r->getX(), r->getY());

				_rooms.push_back(Sprite::create("room.png"));
				_rooms[i]->setPosition(100 + r->getX() * roomWidth / 2, 100 + r->getY() * roomHeight/2);
				_rooms[i]->setScale(0.5, 0.5);
				_map->addChild(_rooms[i]);

				i++;
			}
		}
	}

	//add player icon
	_playerIcon = Sprite::create("player_icon.png");
	_playerIcon->setPosition(100 + player->getPosX() * roomWidth / 2, 100 + player->getPosY() * roomHeight / 2);
	_playerIcon->setScale(0.3, 0.3);
	_map->addChild(_playerIcon);

	_map->setVisible(false);
}

void EntryPoint::_updateMap()
{
	//room size
	_room = Sprite::create("room.png");
	Size size = _room->getContentSize();
	float roomWidth = size.width;
	float roomHeight = size.height;

	//move player icon
	_playerIcon->setPosition(100 + player->getPosX() * roomWidth / 2, 100 + player->getPosY() * roomHeight / 2);

	//put map on top of every other sprites
	auto spriteParent = _map->getParent();
	spriteParent->reorderChild(_map, (int)spriteParent->getChildrenCount() - 1);
}


void EntryPoint::SpawnPlayer()
{
	_player = Sprite::create("mob_1.png");
	_player->setPosition(ScreenWidth / 2, ScreenHeight / 2);
	_player->setScale(1.1, 1.1);
	_parent->addChild(_player);
}

/*
void EntryPoint::MovePlayer(Vec3 pos)
{
	_player->runAction(
		// action is a sequence of actions
		Sequence::create(
			// first wait 0.2f seconds
			DelayTime::create(0.2f),
			// then zoom and fade the sprite
			Spawn::createWithTwoActions(
				//ScaleTo::create(0.5f, _player->getScale() * 2.0f),
				MoveTo::create(5, pos),
				// then fade out the sprite
				FadeTo::create(0.5f, 0)),
			// destroy the sprite at the end
			RemoveSelf::create(),
			CallFunc::create()
			nullptr
		));
}
*/

void EntryPoint::_SpawnEnemy()
{
	Room* actualRoom = dungeon->getRoom(player->getPosX(), player->getPosY());
	Enemy* E = actualRoom->getEnemy1();
	tempName = enemiesSprites[E->GetSprite()];
	_enemy = Sprite::create(tempName);
	_enemy->setPosition(E->GetPosX(),E->GetPosY());
	_enemy->setScale(1.5, 1.5);
	//_treasure->setScale((rand() % 30) / 10.0f + 2.0f);
	_parent->addChild(_enemy);

	Enemy* E2 = actualRoom->getEnemy2();
	tempName = enemiesSprites[E2->GetSprite()];
	_enemy2 = Sprite::create(tempName);
	_enemy2->setPosition(E2->GetPosX(), E2->GetPosY());
	_enemy2->setScale(1.5, 1.5);
	//_treasure->setScale((rand() % 30) / 10.0f + 2.0f);
	_parent->addChild(_enemy2);
}

void EntryPoint::_AddDoorLeft() {
	_doorLeft = Sprite::create("door.png");
	_doorLeft->setPosition(25, ScreenHeight / 2);
	_doorLeft->setScale(0.15, 0.15);
	_doorLeft->setRotation(180);
	_parent->addChild(_doorLeft);
}
void EntryPoint::_AddDoorRight() {
	_doorRight = Sprite::create("door.png");
	_doorRight->setPosition(ScreenWidth-25, ScreenHeight / 2);
	_doorRight->setScale(0.15, 0.15);;
	_parent->addChild(_doorRight);
}
void EntryPoint::_AddDoorUp() {
	_doorUp = Sprite::create("door.png");
	_doorUp->setPosition(ScreenWidth / 2, ScreenHeight-30);
	_doorUp->setRotation(-90);
	_doorUp->setScale(0.15, 0.15);
	_parent->addChild(_doorUp);
}
void EntryPoint::_AddDoorDown() {
	_doorDown = Sprite::create("door.png");
	_doorDown->setPosition(ScreenWidth / 2, 25);
	_doorDown->setRotation(90);
	_doorDown->setScale(0.15, 0.15);
	_parent->addChild(_doorDown);
}

void EntryPoint::Update(float delta_time)
{
	_total_time += delta_time;
	_time_label->setString(std::to_string(player->getPosX())+ " " +std::to_string(player->getPosY()));

}

void EntryPoint::Touch(cocos2d::Vec2 position, bool down)
{
	if (down)
	{
		// display coords touched
		std::stringstream ss;
		ss << position.x << " " << position.y << std::endl;
		
		if (_mapButton) {
			// convert coordinates to the treasure coordinations
			auto node_p = _mapButton->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _mapButton->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height) _mapOnOff();
			else if (_map->isVisible()) _mapOnOff();//auto close map when click
		}
		if (_treasure)
		{
			Room* actualRoom = dungeon->getRoom(player->getPosX(), player->getPosY());
			// convert coordinates to the treasure coordinations
			auto node_p = _treasure->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _treasure->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				// create the sprite with open chest
				auto treasure_open = Sprite::create("chest_open.png");
				treasure_open->setPosition(_treasure->getPosition());
				treasure_open->setScale(_treasure->getScale());
				_parent->addChild(treasure_open);
				// play a sound
				SimpleAudioEngine::getInstance()->playEffect("treasure.wav");
				// run a complex action
				treasure_open->runAction(
					// action is a sequence of actions
					Sequence::create(
						// first wait 0.2f seconds
						DelayTime::create(0.2f),
						// then zoom and fade the sprite
						Spawn::createWithTwoActions(
							ScaleTo::create(0.5f, treasure_open->getScale() * 2.0f),
							// then fade out the sprite
							FadeTo::create(0.5f, 0)),
						// destroy the sprite at the end
						RemoveSelf::create(),
						nullptr
					));

				int gold = randomInt(5, 10);
				player->AddGold(gold);

				auto gold_get = Label::createWithTTF(std::to_string(gold) + " Golds", DEFAULT_FONT, 36);
				gold_get->setTextColor(Color4B::YELLOW);
				gold_get->setPosition(_treasure->getPosition());
				_parent->addChild(gold_get);
				// run a complex action
				gold_get->runAction(
					// action is a sequence of actions
					Sequence::create(
						// then zoom and fade the sprite
						MoveTo::create(1.2, Vec2(gold_get->getPosition().x, gold_get->getPosition().y + 60)),
						// destroy the sprite at the end
						RemoveSelf::create(),
						nullptr
					));
				actualRoom->TakeChest();
				_gold_label->setString("Player gold : " + std::to_string(player->getGold()));
				_treasure->removeFromParent();
				_treasure = nullptr;
			}
		}
		if (_doorLeft->isVisible()) {
			// convert coordinates to the treasure coordinations
			auto node_p = _doorLeft->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _doorLeft->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				_player->runAction(
					// action is a sequence of actions
					Sequence::create(
						// first wait 0.2f seconds
						DelayTime::create(0.2f),
						MoveTo::create(2, _doorLeft->getPosition()),
						// then zoom and fade the sprite

						// destroy the sprite at the end
						RemoveSelf::create(),
						CallFunc::create([=] {
							player->moveLeft();
							ClearRoom();
							EnterRoom();
							SpawnPlayer();
							}),
						nullptr
								));
			}
		}
		if (_doorRight->isVisible()) {
			// convert coordinates to the treasure coordinations
			auto node_p = _doorRight->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _doorRight->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				_player->runAction(
					// action is a sequence of actions
					Sequence::create(
						// first wait 0.2f seconds
						DelayTime::create(0.2f),
						MoveTo::create(2, _doorRight->getPosition()),
						// then zoom and fade the sprite

						// destroy the sprite at the end
						RemoveSelf::create(),
						CallFunc::create([=] {
							player->moveRight();
							ClearRoom();
							EnterRoom();
							SpawnPlayer();
							}),
						nullptr
								));
			}

		}
		if (_doorUp->isVisible()) {
			// convert coordinates to the treasure coordinations
			auto node_p = _doorUp->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _doorUp->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				_player->runAction(
					// action is a sequence of actions
					Sequence::create(
						// first wait 0.2f seconds
						DelayTime::create(0.2f),
						MoveTo::create(2, _doorUp->getPosition()),
						// then zoom and fade the sprite
						
						// destroy the sprite at the end
						RemoveSelf::create(),
						CallFunc::create([=] {
							player->moveUp();
							ClearRoom();
							EnterRoom();
							SpawnPlayer(); 
						}),
						nullptr
					));


			}
		}
		if (_doorDown->isVisible()) {
			// convert coordinates to the treasure coordinations
			auto node_p = _doorDown->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _doorDown->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				_player->runAction(
					// action is a sequence of actions
					Sequence::create(
						// first wait 0.2f seconds
						DelayTime::create(0.2f),
						MoveTo::create(2, _doorDown->getPosition()),
						// then zoom and fade the sprite

						// destroy the sprite at the end
						RemoveSelf::create(),
						CallFunc::create([=] {
							player->moveDown();
							ClearRoom();
							EnterRoom();
							SpawnPlayer();
							}),
						nullptr
								));
			}
		}

		if (_enemy) {
			// convert coordinates to the treasure coordinations
			auto node_p = _enemy->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _enemy->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				SimpleAudioEngine::getInstance()->playEffect("treasure.wav");
			}
		}

		if (_enemy2) {
			// convert coordinates to the treasure coordinations
			auto node_p = _enemy2->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _enemy2->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				SimpleAudioEngine::getInstance()->playEffect("treasure.wav");
			}
		}
	}

}

//return a random int beetween min(inclusive) and max(inclusive)
int EntryPoint::randomInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}