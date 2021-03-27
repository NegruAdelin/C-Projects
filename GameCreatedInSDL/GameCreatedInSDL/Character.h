#pragma once
#include "libs.h"

class Character {
public:
	virtual void move(SDL_Rect collider) = 0;
	virtual void move() = 0;
	virtual void render(SDL_Renderer* render, Texture& texture) = 0;
	virtual void handleEvent(SDL_Event& e, int& attackAnimationTime, int cooldown) = 0;

	virtual int getPosX() = 0;
	virtual int getPosY() = 0;
	virtual int getVelX() = 0;
	virtual int getVelY() = 0;
	virtual int getCharacterWidth() = 0;
	virtual int getCharacterHeight() = 0;
	virtual SDL_Rect getCollider() = 0;
	virtual SDL_RendererFlip getFlip() = 0;

	virtual void setPosX(int x) = 0;
	virtual void setPosY(int y) = 0;
	virtual void setCollisionCoordinates(int x, int y) = 0;
	virtual void setCollider(SDL_Rect r) = 0;
	virtual void setFlip(SDL_RendererFlip flip) = 0;
	virtual void setVelY(int velY) = 0;
	virtual void setVelX(int velX) = 0;

};