#include "Dungeon.h"
#include "EntryPoint.h"
#include <vector>


Dungeon::Dungeon(int sizeX, int sizeY) {
	for (int i = 0; i <= sizeX; i++) {
		std::vector<Room*> Line;
		for (int j = 0; j <= sizeY; j++) {
			Line.push_back(nullptr);
		}
		AllRoom.push_back(Line);
	}
}
