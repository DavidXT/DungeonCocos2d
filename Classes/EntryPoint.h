#pragma once

#include "cocos2d.h"

class EntryPoint
{
public:
	void Init(cocos2d::Node *parent);

	void Update(float delta_time);
	// position is screen position of the touch
	// down is true if it's pressing.
	// down is false if the touch is released
	void Touch(cocos2d::Vec2 position, bool down);
	int randomInt(int, int);

protected:

	//New room cleaning system
	void ClearRoom();
	void ClearPlayer();
	void ClearPlayerAnim();
	void EnterRoom();

	//Spawn object in rooms
	void _AddTreasure();
	void _SpawnEnemy();
	void _SpawnExit();
	void _SpawnPlayer();

	//Door systems
	void _AddDoorLeft();
	void _AddDoorRight();
	void _AddDoorUp();
	void _AddDoorDown();
	void _updateDoor();


	//Player movment functions
	void DisableDoors();
	void _MovePlayer(cocos2d::Sprite* object, std::string direction);
	void UpdatePlayerPos(std::string direction);
	void UpdatePlayerSprite(std::string direction);

	//Minimap system
	void _DrawMap();
	void _mapOnOff() { _map->setVisible(!_map->isVisible()); }
	void _updateMap();
	

	//Values
	cocos2d::Node* _parent{ nullptr };
	cocos2d::Label* _gold_label{ nullptr };
	cocos2d::Label* _time_label{ nullptr };
	cocos2d::Sprite* _treasure{ nullptr };
	cocos2d::Sprite* _enemy{ nullptr };
	cocos2d::Sprite* _enemy2{ nullptr };
	cocos2d::Sprite* _background{ nullptr };
	cocos2d::Sprite* _player { nullptr };
	cocos2d::Sprite* _newPlayer { nullptr };
	cocos2d::Sprite* _tempSprite{ nullptr };
	cocos2d::Sprite* _doorLeft{ nullptr };
	cocos2d::Sprite* _doorRight{ nullptr };
	cocos2d::Sprite* _doorUp{ nullptr };
	cocos2d::Sprite* _doorDown{ nullptr };
	cocos2d::Sprite* _mapButton{ nullptr };
	cocos2d::Sprite* _map{ nullptr };
	cocos2d::Sprite* _room{ nullptr };
	cocos2d::Sprite* _playerIcon{ nullptr };
	cocos2d::Sprite* _exit{ nullptr };
	std::vector<cocos2d::Sprite*> _rooms;
	float _total_time{ 0 };
};

