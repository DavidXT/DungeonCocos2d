#include "Dungeon.h"
#include "EntryPoint.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

Dungeon::Dungeon(int nbRoom,int sizeX, int sizeY) {
	for (int i = 0; i <= sizeX; i++) {
		std::vector<Room*> Line;
		for (int j = 0; j <= sizeY; j++) {
			Line.push_back(nullptr);
		}
		AllRoom.push_back(Line);
	}
	AllRoom[0][0] = new Room(0, 0);
	int currentX = 0;
	int currentY = 0;
	for (int j = 0; j <= nbRoom; j++) {
		int tmp =  rand() % 2;
		if (tmp == 0) {
			currentX++;
			if (AllRoom[currentX][currentY] == nullptr) {
				AllRoom[currentX][currentY] = new Room(currentX, currentY);
			}
			else if (AllRoom[currentX][currentY] != nullptr) {
				currentY++;
				AllRoom[currentX][currentY] = new Room(currentX, currentY);
			}
		}
		else {
			currentY++;
			if (AllRoom[currentX][currentY] == nullptr) {
				AllRoom[currentX][currentY] = new Room(currentX, currentY);
			}
			else if(AllRoom[currentX][currentY] != nullptr){
				currentX++;
				AllRoom[currentX][currentY] = new Room(currentX, currentY);
			}
		}
	}
}

Room* Dungeon::getRoom(int x, int y) {
	return AllRoom[x][y];
}

