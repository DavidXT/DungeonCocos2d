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

protected:
	void ClearRoom();
	void EnterRoom();

	void _AddTreasure();
	void _SpawnEnemy();
	void _AddDoorLeft();
	void _AddDoorRight();
	void _AddDoorUp();
	void _AddDoorDown();
	void SpawnDoor();
	

	cocos2d::Node* _parent{ nullptr };
	cocos2d::Label* _touch_label{ nullptr };
	cocos2d::Label* _time_label{ nullptr };
	cocos2d::Sprite* _treasure{ nullptr };
	cocos2d::Sprite* _enemy{ nullptr };
	cocos2d::Sprite* _enemy2{ nullptr };
	cocos2d::Sprite* _background{ nullptr };
	cocos2d::Sprite* _tempSprite{ nullptr };
	cocos2d::Sprite* _doorLeft{ nullptr };
	cocos2d::Sprite* _doorRight{ nullptr };
	cocos2d::Sprite* _doorUp{ nullptr };
	cocos2d::Sprite* _doorDown{ nullptr };
	float _total_time{ 0 };
};

