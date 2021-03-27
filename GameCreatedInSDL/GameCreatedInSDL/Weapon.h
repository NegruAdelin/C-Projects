#pragma once
#include "libs.h"

enum AttackDirection{
	ATTACK_LEFT,
	ATTACK_RIGHT
};

class Weapon {
public :
	static const int RANGE_WEAPON = 40;
	static const int HEIGHT_WEAPON = 29;
	static const int ATTACK_VALUE = 5;
	static const int ATTACK_SPEED = 30;

	Weapon();
	void render(SDL_Renderer* render, Texture& texture, SDL_RendererFlip flip);

	int getPosX();
	int getPosY();
	int getRange();
	int getAttackValue();
	int getAttackSpeed();
	SDL_Rect getCollider();

	void setPosX(int x);
	void setPosY(int y);
	void setRange(int range);
	void setAttackValue(int attackValue);
	void setAttackSpeed(int attackSpeed);
	void setCollider(SDL_Rect collider);
	void setCollider(int x, int y, int w, int h);

protected:
	int _posX, _posY;
	int _range, _attackValue, _attackSpeed;
	SDL_Rect collider;
};