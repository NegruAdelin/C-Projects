#include "Frame.h"

void Frame::cls() {
	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;

	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hOut, cursorPosition);
}

void Frame::refreshFrame(const Map map, const Player player) {
	cls();
	printFrame(map, player);
}

void Frame::printFrame(Map map, Player player) {
	//Print the Map with the Player and Walls
	int mapLine = map.getLine(), mapSize = map.getMap().size();
	std::vector<int> auxMap = map.getMap();
	std::vector<int> auxTrap = map.getTraps();
	int positionPlayer = player.getPosition();

	for (int i = 0; i < mapSize; i++) {
		if (i % mapLine == 0) {
			std::cout << std::endl << "\t";
		}

		if (positionPlayer == i) {
			std::cout << "P ";
		}
		else {
			switch (auxMap[i]) {
			case 0: std::cout << "_ ";
				break;
			case 1: std::cout << (char)2 << " ";
				break;
			case 2: std::cout << "X ";
				break;
			default: std::cout << "Is default case";
				break;
			}
		}
	}
}