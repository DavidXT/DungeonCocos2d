#include "Dungeon.h"
#include "EntryPoint.h"
#include "SimpleAudioEngine.h"
#include <vector>
USING_NS_CC;
using namespace CocosDenshion;

Dungeon::Dungeon(int nbRoom,int X, int Y) {
	sizeX = X;
	sizeY = Y;
	for (int i = 0; i <= sizeX; i++) {
		std::vector<Room*> Line;
		for (int j = 0; j <= sizeY; j++) {
			Line.push_back(nullptr);
		}
		AllRoom.push_back(Line);
	}
	AllRoom[sizeX/2][sizeY/2] = new Room(sizeX/2, sizeY/2);
	int currentX;
	int currentY;
	int j = 0;
	do {
		currentX = rand() % sizeX;
		currentY = rand() % sizeY;
		if (currentX == 0) {
			if (currentY == 0) {
				if (AllRoom[currentX + 1][currentY] != nullptr || AllRoom[currentX][currentY + 1] != nullptr) {
					if (AllRoom[currentX][currentY] == nullptr) {
						AllRoom[currentX][currentY] = new Room(currentX, currentY);
						j++;
					}
				}
			}
			else {
				if (AllRoom[currentX + 1][currentY] != nullptr || AllRoom[currentX][currentY + 1] != nullptr || AllRoom[currentX][currentY - 1]) {
					if (AllRoom[currentX][currentY] == nullptr) {
						AllRoom[currentX][currentY] = new Room(currentX, currentY);
						j++;
					}
				}
			}

		}
		else if (currentY == 0) {
			if (AllRoom[currentX + 1][currentY] != nullptr || AllRoom[currentX - 1][currentY] != nullptr || AllRoom[currentX][currentY + 1] != nullptr) {
				if (AllRoom[currentX][currentY] == nullptr) {
					AllRoom[currentX][currentY] = new Room(currentX, currentY);
					j++;
				}
			}
		}
		else {
			if (AllRoom[currentX + 1][currentY] != nullptr || AllRoom[currentX - 1][currentY] != nullptr || AllRoom[currentX][currentY + 1] != nullptr || AllRoom[currentX][currentY - 1]) {
				if (AllRoom[currentX][currentY] == nullptr) {
					AllRoom[currentX][currentY] = new Room(currentX, currentY);
					j++;
				}
			}
		}
	} while (j <= nbRoom);
}

Room* Dungeon::getRoom(int x, int y) {
	return AllRoom[x][y];
}

