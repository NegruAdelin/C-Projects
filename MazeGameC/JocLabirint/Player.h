#pragma once
#include <iostream>
#include "Map.h"

class Player {
private:
	int _pos;
public:
	Player() : _pos(0) {};
	
	Player(int pos) : _pos(pos) {};

	Player(const Player& player) {
		this->_pos = player._pos;
	}

	void setPosition(int pos) {
		this->_pos = pos;
	}

	int getPosition() const{
		return this->_pos;
	}

	//check if is a trap near a player
	bool isAtrap(int pos, std::vector<int> traps) {
		return (std::find(traps.begin(), traps.end(), pos) == traps.end() || (traps.end() == traps.begin())) ?  false : true;
	};

	//disarm the trap
	void disarmTrap(int, std::vector<int>&);

	void playerMove(int, Map);
	
	bool obstacle(int pos, std::vector<int> v) {
		if (v[pos] == 1) {
			return true;
		}
		else {
			return false;
		}
	}

	//check if the player is on a trap an return if is dead or not
	bool isDead(std::vector<int>);

	bool playerWin(int exit) {
		return (this->_pos == exit) ? true : false;
	};
};