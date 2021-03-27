#pragma once
#include "libs.h"

class Dot {
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	Dot();
	void generatePosition(Character* player);
	void render(SDL_Renderer* renderer, Texture& texture);
	int getPosX();
	int getPosY();
	SDL_Rect getCollider();

protected:
	int _posX, _posY;
	SDL_Rect collider;
};