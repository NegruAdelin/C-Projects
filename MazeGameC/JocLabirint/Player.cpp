#include "Player.h"

void Player::playerMove(int direction, Map map) {
	
	int mapLine = map.getLine(), mapSize = map.getMap().size();

	switch (direction){
	case 72: {
		if (this->_pos - mapLine >= 0 &&
			!obstacle(this->_pos - mapLine, map.getMap())) {
			this->_pos -= mapLine;
		}
	}
		   break;
	case 80: {
		if (this->_pos + mapLine < mapSize &&
			!obstacle(this->_pos + mapLine, map.getMap())) {
			this->_pos += mapLine;
		}
	}
		   break;
	case 77: {
		if ((this->_pos + 1) % mapLine &&
			!obstacle(this->_pos + 1, map.getMap())) {
			this->_pos += 1;
		}
	}
		   break;
	case 75: {
		if ((this->_pos - 1) % mapLine != (mapLine - 1) &&
			!obstacle(this->_pos - 1, map.getMap())) {
			this->_pos -= 1;
		}
	}
		   break;
	
	default:
		break;
	}
}

void Player::disarmTrap(int pos, std::vector<int> &traps) {
	for (int i = 0; i < traps.size(); i++) {
		if (traps[i] == pos) {
			traps.erase((traps.begin() + i));
			traps.shrink_to_fit();
			break;
		}
	}
}

bool Player::isDead(std::vector<int>traps) {
	for (int i = 0; i < traps.size(); i++) {
		if (this->_pos == traps[i])
			return true;
	}

	return false;
}

