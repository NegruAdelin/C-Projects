#include "libs.h"

Weapon::Weapon() {
	_posX = 0;
	_posY = 0;
	
	_range = RANGE_WEAPON;
	_attackValue = ATTACK_VALUE;
	_attackSpeed = ATTACK_SPEED;

	collider.w = RANGE_WEAPON;
	collider.h = HEIGHT_WEAPON * 2;

	collider.x = 0;
	collider.y = 0;
}

void Weapon::render(SDL_Renderer* render, Texture& texture, SDL_RendererFlip flip) {
	texture.render(render, _posX, _posY, NULL, 0.0, NULL, flip);
}

int Weapon::getPosX() {
	return _posX;
}

int Weapon::getPosY() {
	return _posY;
}

int Weapon::getRange() {
	return _range;
}

int Weapon::getAttackValue() {
	return _attackValue;
}

int Weapon::getAttackSpeed() {
	return _attackSpeed;
}

SDL_Rect Weapon::getCollider() {
	return collider;
}

void Weapon::setPosX(int x) {
	_posX = x;
	collider.x = _posX;
}

void Weapon::setPosY(int y) {
	_posY = y;
	collider.y = _posY;
}

void Weapon::setRange(int range) {
	_range = range;
}

void Weapon::setAttackValue(int attackValue) {
	_attackValue = attackValue;
}

void Weapon::setAttackSpeed(int attackSpeed) {
	_attackSpeed = attackSpeed;
}

void Weapon::setCollider(SDL_Rect collider) {
	this->collider = collider;
}

void Weapon::setCollider(int x, int y, int w, int h) {
	collider.x = x;
	collider.y = y;
	collider.w = w;
	collider.h = h;
}