#include "EntryPoint.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "Dungeon.h"


USING_NS_CC;
using namespace CocosDenshion;

const std::string DEFAULT_FONT = "fonts/Arial.ttf";
const int ScreenWidth = 1024;
const int ScreenHeight = 768;
Dungeon dungeon;

void EntryPoint::Init(Node *parent)
{
	_parent = parent;
	// labels
	_touch_label = Label::createWithTTF("Hello World", DEFAULT_FONT, 24);
	_touch_label->setPosition(100, 100);

	_time_label = Label::createWithTTF("", DEFAULT_FONT, 24);
	_time_label->setPosition(0, 0);
	_time_label->setAnchorPoint(Vec2(0, 0));

	_parent->addChild(_touch_label);
	_parent->addChild(_time_label);

	// button
	auto button_callback = [=](Ref*) {
		_touch_label->setString("Button pressed");
	};
	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", button_callback);
	float x = ScreenWidth - closeItem->getContentSize().width/2;
	float y = closeItem->getContentSize().height/2;
	closeItem->setPosition(Vec2(x,y));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	parent->addChild(menu, 1);
	_AddDoorLeft();
	_AddDoorRight();
	_AddDoorUp();
	_AddDoorDown();

	_AddTreasure();
}

void EntryPoint::_AddTreasure()
{

	_treasure = Sprite::create("chest_closed.png");
	_treasure->setPosition(rand()%(ScreenWidth/2) + 100, rand()%(ScreenHeight/2) + 200);
	_treasure->setScale((rand() % 30) / 10.0f + 2.0f);
	_parent->addChild(_treasure);

}

void EntryPoint::_AddDoorLeft() {
	_doorLeft = Sprite::create("door.png");
	_doorLeft->setPosition(20, ScreenHeight / 2);
	_doorLeft->setScale(0.1, 0.1);
	_parent->addChild(_doorLeft);
}
void EntryPoint::_AddDoorRight() {
	_doorRight = Sprite::create("door.png");
	_doorRight->setPosition(ScreenWidth, ScreenHeight / 2);
	_doorRight->setScale(0.1, 0.1);
	_parent->addChild(_doorRight);
}
void EntryPoint::_AddDoorUp() {
	_doorUp = Sprite::create("door.png");
	_doorUp->setPosition(ScreenWidth / 2, ScreenHeight);
	_doorUp->setScale(0.1, 0.1);
	_parent->addChild(_doorUp);
}
void EntryPoint::_AddDoorDown() {
	_doorDown = Sprite::create("door.png");
	_doorDown->setPosition(ScreenWidth / 2, 20);
	_doorDown->setScale(0.1, 0.1);
	_parent->addChild(_doorDown);
}

void EntryPoint::Update(float delta_time)
{
	_total_time += delta_time;
	_time_label->setString(std::to_string(dungeon.X)+ " " +std::to_string(dungeon.Y));
}

void EntryPoint::Touch(cocos2d::Vec2 position, bool down)
{
	if (down)
	{
		// display coords touched
		std::stringstream ss;
		ss << position.x << " " << position.y << std::endl;
		_touch_label->setString(ss.str());

		if (_treasure)
		{
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
				_treasure->removeFromParent();
				_treasure = nullptr;
				_AddTreasure();
			}
		}
		if (_doorLeft) {
			// convert coordinates to the treasure coordinations
			auto node_p = _doorLeft->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _doorLeft->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				dungeon.X--;
			}
		}
		if (_doorRight) {
			// convert coordinates to the treasure coordinations
			auto node_p = _doorRight->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _doorRight->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				dungeon.X++;
			}

		}
		if (_doorUp) {
			// convert coordinates to the treasure coordinations
			auto node_p = _doorUp->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _doorUp->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				dungeon.Y++;
			}
		}
		if (_doorDown) {
			// convert coordinates to the treasure coordinations
			auto node_p = _doorDown->convertToNodeSpace(position);
			// get the size of the treasure
			auto cs = _doorDown->getContentSize();
			// check if the touch position is inside
			if (node_p.x >= 0 && node_p.y >= 0 && node_p.x < cs.width && node_p.y < cs.height)
			{
				dungeon.Y--;
			}
		}


	}
}

