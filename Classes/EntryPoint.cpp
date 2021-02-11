#include "EntryPoint.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "Dungeon.h"
#include <time.h>

USING_NS_CC;
using namespace CocosDenshion;

std::vector<std::string> enemiesSprites;
bool canClick = true;
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
	_gold_label = Label::createWithTTF("0", DEFAULT_FONT, 24);
	_gold_label->setTextColor(Color4B::YELLOW);
	_gold_label->setPosition(1000, 750);

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
	_SpawnPlayer();
	_DrawMap();
}

/// <summary>
/// Spawn treasure in room
/// </summary>
void EntryPoint::_AddTreasure()
{
	Room* actualRoom = dungeon->getRoom(player->getPosX(), player->getPosY());
	_treasure = Sprite::create("chest_closed.png");
	_treasure->setPosition(actualRoom->getTreasurePosX(), actualRoom->getTreasurePosY());
	_treasure->setScale(2,2);
	//_treasure->setScale((rand() % 30) / 10.0f + 2.0f);
	_parent->addChild(_treasure);
}

/// <summary>
/// Clear and remove player sprite
/// </summary>
void EntryPoint::ClearPlayer()
{
	if (_player != nullptr) {
		_player->removeFromParent();
		_player = nullptr;
	}
}

/// <summary>
/// Clear and remove player with anim. sprite (when player move)
/// </summary>
void EntryPoint::ClearPlayerAnim()
{
	if (_newPlayer != nullptr) {
		_newPlayer->removeFromParent();
		_newPlayer = nullptr;
	}
}

/// <summary>
/// Delete all sprite if they exist
/// </summary>
void EntryPoint::ClearRoom()
{
	ClearPlayer();
	ClearPlayerAnim();

	if (_enemy != nullptr) {
		_enemy->removeFromParent();
		_enemy = nullptr;
	}
	if (_enemy2 != nullptr) {
		_enemy2->removeFromParent();
		_enemy2 = nullptr;
	}

	if (_treasure != nullptr)
	{
		_treasure->removeFromParent();
		_treasure = nullptr;
	}
	if (_exit != nullptr) {
		_exit->removeFromParent();
		_exit = nullptr;
	}
}


/// <summary>
/// Check each condition for the generation of the room
/// </summary>
void EntryPoint::EnterRoom()
{
	Room* actualRoom = dungeon->getRoom(player->getPosX(), player->getPosY());
	_updateDoor();
	if (actualRoom->getTreasure()) {
		_AddTreasure();
	}
	if (dungeon->getWinX() == player->getPosX() && dungeon->getWinY() == player->getPosY()) {
		_SpawnExit();
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

/// <summary>
/// Spawn Player Sprite in center of the room
/// </summary>
void EntryPoint::_SpawnPlayer()
{
	_player = Sprite::create("player.png");
	_player->setPosition(ScreenWidth / 2, ScreenHeight / 2);
	_player->setScale(1.5, 1.5);
	_parent->addChild(_player);
}

/// <summary>
/// Spawn exit door in the room
/// </summary>
void EntryPoint::_SpawnExit() {
	_exit = Sprite::create("exit.png");
	_exit->setPosition(400, 400);
	_exit->setScale(1.1, 1.1);
	_parent->addChild(_exit);
}

/// <summary>
/// Spawn enemy in room if room have enemy
/// </summary>
void EntryPoint::_SpawnEnemy()
{
	Room* actualRoom = dungeon->getRoom(player->getPosX(), player->getPosY());
	if (actualRoom->getHaveE1()) {
		Enemy* E = actualRoom->getEnemy1();
		tempName = enemiesSprites[E->GetSprite()];
		_enemy = Sprite::create(tempName);
		_enemy->setPosition(E->GetPosX(), E->GetPosY());
		_enemy->setScale(1.5, 1.5);
		//_treasure->setScale((rand() % 30) / 10.0f + 2.0f);
		_parent->addChild(_enemy);
	}

	if (actualRoom->getHaveE2()) {
		Enemy* E2 = actualRoom->getEnemy2();
		tempName = enemiesSprites[E2->GetSprite()];
		_enemy2 = Sprite::create(tempName);
		_enemy2->setPosition(E2->GetPosX(), E2->GetPosY());
		_enemy2->setScale(1.5, 1.5);
		//_treasure->setScale((rand() % 30) / 10.0f + 2.0f);
		_parent->addChild(_enemy2);
	}
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
	if (down == true || canClick == true)
	{
		canClick = false;
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
				_gold_label->setString(std::to_string(player->getGold()));
				
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

				_MovePlayer(_doorLeft, "left");
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
			
				_MovePlayer(_doorRight, "right");
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
				_MovePlayer(_doorUp, "up");
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
				_MovePlayer(_doorDown, "down");
			}
		}

		if (_enemy) {
			Room* actualRoom = dungeon->getRoom(player->getPosX(), player->getPosY());
			// convert coordinates to the treasure coordinations
			auto node_p = _enemy->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _enemy->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				SimpleAudioEngine::getInstance()->setEffectsVolume(0.7);
				SimpleAudioEngine::getInstance()->playEffect("explode.wav");
				actualRoom->killE1();
				_enemy->removeFromParent();
				_enemy = nullptr;
			}
		}

		if (_enemy2) {
			Room* actualRoom = dungeon->getRoom(player->getPosX(), player->getPosY());
			// convert coordinates to the treasure coordinations
			auto node_p = _enemy2->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _enemy2->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				SimpleAudioEngine::getInstance()->setEffectsVolume(0.7);
				SimpleAudioEngine::getInstance()->playEffect("explode.wav");
				actualRoom->killE2();
				_enemy2->removeFromParent();
				_enemy2 = nullptr;
			}
		}
		if (_exit) {
			// convert coordinates to the treasure coordinations
			auto node_p = _exit->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _exit->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				Director::getInstance()->end();
			}
		}
	}

}

//return a random int beetween min(inclusive) and max(inclusive)
int EntryPoint::randomInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}


//Player movement system functions

/// <summary>
/// Move player to an another room
/// </summary>
/// <param name="object"> Door sprite object </param>
/// <param name="direction"> Direction for player movement </param>
void EntryPoint::_MovePlayer(cocos2d::Sprite* object, std::string direction)
{
	DisableDoors();
	UpdatePlayerSprite(direction);

	_newPlayer->runAction(
		// action is a sequence of actions
		Sequence::create(
			// first wait 0.2f seconds
			//DelayTime::create(0.1f),
			CallFunc::create([=] {
				SimpleAudioEngine::getInstance()->playEffect("running.wav");
				}),

			MoveTo::create(2, object->getPosition()),
			// then zoom and fade the sprite

			// destroy the sprite at the end
			RemoveSelf::create(),
			CallFunc::create([=] {
				UpdatePlayerPos(direction);
				ClearRoom();
				EnterRoom();
				_SpawnPlayer();
				canClick = true;
				}),
			nullptr
					));

}

/// <summary>
/// Update player position coordinates
/// </summary>
/// <param name="direction"> Direction for player movement </param>
void EntryPoint::UpdatePlayerPos(std::string direction)
{
	if (direction == "down")
	{
		player->moveDown();
	}
	if (direction == "up")
	{
		player->moveUp();
	}
	if (direction == "left")
	{
		player->moveLeft();
	}
	if (direction == "right")
	{
		player->moveRight();
	}
}

/// <summary>
/// Update player sprite depend of choose direction
/// </summary>
/// <param name="direction"> Direction for player movement </param>
void EntryPoint::UpdatePlayerSprite(std::string direction)
{
	if (direction == "down")
	{
		_newPlayer = Sprite::create("player_down.png");
	}
	if (direction == "up")
	{
		_newPlayer = Sprite::create("player_up.png");
	}
	if (direction == "left")
	{
		_newPlayer = Sprite::create("player_left.png");
	}
	if (direction == "right")
	{
		_newPlayer = Sprite::create("player_right.png");
	}

	_newPlayer->setPosition(_player->getPosition());
	_newPlayer->setScale(_player->getScale());
	_parent->addChild(_newPlayer);

	ClearPlayer();
}

/// <summary>
/// Disable all door sprites to prevent spam click
/// </summary>
void EntryPoint::DisableDoors()
{
	if(_doorDown != nullptr)
		_doorDown->setVisible(false);
	if (_doorUp != nullptr)
		_doorUp->setVisible(false);
	if (_doorLeft != nullptr)
		_doorLeft->setVisible(false);
	if (_doorRight != nullptr)
		_doorRight->setVisible(false);
}
