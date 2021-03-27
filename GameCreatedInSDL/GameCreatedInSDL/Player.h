#pragma once
#include "libs.h"


class Player : public Character {
public:
	static const int PLAYER_WIDTH = 20;
	static const int PLAYER_HEIGHT = 20;
	static const int PLAYER_VEL = 3;

	Player();
	void move(SDL_Rect colision) override;
	void move() override;
	void render(SDL_Renderer* renderer, Texture& texture) override;
	void handleEvent(SDL_Event &e, int& attackTime, int cooldown) override;
	
	int getPosX() override;
	int getPosY() override;
	int getVelX() override;
	int getVelY() override;
	int getCharacterWidth() override;
	int getCharacterHeight() override;
	SDL_Rect getCollider() override;
	SDL_RendererFlip getFlip() override;

	void setPosX(int x) override;
	void setPosY(int y) override;
	void setCollisionCoordinates(int x, int y) override;
	void setCollider(SDL_Rect r) override;
	void setFlip(SDL_RendererFlip flip) override;
	void setVelY(int velY) override;
	void setVelX(int velX) override;

protected:
	int _posX, _posY;
	int _velX, _velY;
	SDL_Rect collider;
	SDL_RendererFlip _flip;
};