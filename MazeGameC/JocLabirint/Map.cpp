#include "Map.h"

void Map::createWalls() {
	srand(time(NULL));

	int end = this->_map.size();
	for (int i = 0; i < this->_numberWalls; i++) {
		int randomWallPosition;

		do {
			randomWallPosition = rand() % end;
		} while (this->_map[randomWallPosition] == 1 
			|| randomWallPosition == this->_exit 
			|| randomWallPosition == this->_start);

		this->_map[randomWallPosition] = 1;
	}
}

void Map::createMap() {
	srand(time(NULL));
	this->_map.clear();

	int end = this->_column * this->_line;
	do {
		this->_exit = rand() % end;
	} while (this->_exit == this->_start);

	for (int i = 0; i < end; i++) {
		if (i == this->_exit)
			this->_map.push_back(2);
		else
			this->_map.push_back(0);
	}
}

void Map::createTraps() {
	srand(time(NULL));
	this->_traps.clear();

	int end = this->_map.size();
	int randomTraps;

	for (int i = 0; i < this->_numberTraps; i++) {

		randomTraps = rand() % end;

		while (this->_map[randomTraps] == 1 || 
			this->_map[randomTraps] == 2 || 
			randomTraps == this->_start ||
			std::find(this->_traps.begin(), this->_traps.end(), randomTraps) != this->_traps.end()) {

			randomTraps = rand() % end;
		}

		this->_traps.push_back(randomTraps);
	}
}

bool Map::mapHasAnExit() {
	std::vector<int>bfs;
	std::vector<int>vizitat;

	bfs.push_back(this->_exit);
	vizitat.push_back(this->_exit);

	while (bfs.begin() != bfs.end() && bfs[0] != this->_start) {

		if (bfs[0] - this->_line >= 0 &&
			this->_map[bfs[0] - this->_line] != 1 &&
			std::find(vizitat.begin(), vizitat.end(), (bfs[0] - this->_line)) == vizitat.end()) {

			bfs.push_back(bfs[0] - this->_line);
			vizitat.push_back(bfs[0] - this->_line);
		}

		if (bfs[0] + this->_line < this->_map.size() &&
			this->_map[bfs[0] + this->_line] != 1 &&
			std::find(vizitat.begin(), vizitat.end(), (bfs[0] + this->_line)) == vizitat.end()) {

			bfs.push_back(bfs[0] + this->_line);
			vizitat.push_back(bfs[0] + this->_line);
		}

		if (bfs[0] - 1 >= 0 &&
			this->_map[bfs[0] - 1] != 1 &&
			std::find(vizitat.begin(), vizitat.end(), (bfs[0] - 1)) == vizitat.end() &&
			((bfs[0] - 1) % _line != 0)) {

			bfs.push_back(bfs[0] - 1);
			vizitat.push_back(bfs[0] - 1);
		}

		if (bfs[0] + 1 < this->_map.size() &&
			this->_map[bfs[0] + 1] != 1 &&
			std::find(vizitat.begin(), vizitat.end(), (bfs[0] + 1)) == vizitat.end() &&
			((bfs[0] + 1) % _line != 0)) {

			bfs.push_back(bfs[0] + 1);
			vizitat.push_back(bfs[0] + 1);
		}

		for (int i = 0; i < bfs.size() - 1; i++) {
			bfs[i] = bfs[i + 1];
		}

		bfs.pop_back();
	}
	if (bfs.end() == bfs.begin()) {
		return false;
	}
	else {
		return true;
	}
}

void Map::cls() {
	COORD cursorPosition;	
	cursorPosition.X = 0;	
	cursorPosition.Y = 0;	

	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hOut, cursorPosition);
}