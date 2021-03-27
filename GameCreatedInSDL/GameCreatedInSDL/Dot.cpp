#include "libs.h"

Dot::Dot() {

	_posX = rand() % (WIDTH - DOT_WIDTH);
	_posY = rand() % (HEIGHT - DOT_HEIGHT);

	collider.w = DOT_WIDTH;
	collider.h = DOT_HEIGHT;

	collider.x = _posX;
	collider.y = _posY;

}

void Dot::generatePosition(Character* player) {
	
	while (checkCollision(collider, player->getCollider())) {
		_posX = rand() % (WIDTH - DOT_WIDTH);
		_posY = rand() % (HEIGHT - DOT_HEIGHT);
		collider.x = _posX;
		collider.y = _posY;
	}

}

void Dot::render(SDL_Renderer* renderer, Texture& texture) {
	
	texture.render(renderer, _posX, _posY);

}

int Dot::getPosX() {
	return _posX;
}

int Dot::getPosY() {
	return _posY;
}

SDL_Rect Dot::getCollider() {
	return collider;
}