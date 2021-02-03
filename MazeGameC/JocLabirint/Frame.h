#pragma once
#include <iostream>
#include "Player.h"
#include "Map.h"

class Frame {
public:
	void cls();

	void refreshFrame(const Map map, const  Player player);
	
	void printFrame(Map map, const Player player);
};