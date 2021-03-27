#include "libs.h"

Enemy::Enemy() {
	_posX = 0;
	_posY = 0;

	collider.w = ENEMY_WIDTH;
	collider.h = ENEMY_HEIGHT;

	_flip = SDL_FLIP_NONE;
}

void Enemy::move(SDL_Rect collision) {
	
	if (_posX > collision.x) {
		_posX -= ENEMY_VEL;
		_flip = SDL_FLIP_NONE;
	}
	else {
		_posX += ENEMY_VEL;
		_flip = SDL_FLIP_HORIZONTAL;
	}
	collider.x = _posX;

	if (_posX < 0 || _posX + ENEMY_WIDTH > WIDTH) {
		_posX -= ENEMY_VEL;
		collider.x = _posX;
	}


	if (_posY > collision.y) {
		_posY -= ENEMY_VEL;
	}
	else {
		_posY += ENEMY_VEL;
	}
	collider.y = _posY;

	if (_posY < 0 || _posY + ENEMY_HEIGHT > HEIGHT) {
		_posY -= ENEMY_VEL;
		collider.y = _posY;
	}
}

void Enemy::move() {
	
}

void Enemy::handleEvent(SDL_Event& e, int& attackTime, int cooldown) {
	
}

void Enemy::render(SDL_Renderer* renderer, Texture& texture) {
	texture.render(renderer, _posX, _posY, NULL, 0, NULL, _flip);
}

int Enemy::getPosX() {
	return this->_posX;
}

int Enemy::getPosY() {
	return this->_posY;
}

int Enemy::getVelX() {
	return 0;
}

int Enemy::getVelY() {
	return 0;
}

int Enemy::getCharacterHeight() {
	return ENEMY_HEIGHT;
}

int Enemy::getCharacterWidth() {
	return ENEMY_WIDTH;
}

SDL_Rect Enemy::getCollider() {
	return this->collider;
}

SDL_RendererFlip Enemy::getFlip() {
	return this->_flip;
}

void Enemy::setPosX(int x) {
	this->_posX = x;
}

void Enemy::setPosY(int y) {
	this->_posY = y;
}

void Enemy::setCollisionCoordinates(int x, int y) {
	this->collider.x = x;
	this->collider.y = y;
}

void Enemy::setCollider(SDL_Rect r){
	this->collider = r;
}

void Enemy::setFlip(SDL_RendererFlip flip) {
	this->_flip = flip;
}

void Enemy::setVelX(int velX) {
	
}

void Enemy::setVelY(int velY) {

}