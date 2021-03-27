#include "libs.h"

Player::Player() {
	_posX = 0;
	_posY = 0;

	collider.w = PLAYER_WIDTH;
	collider.h = PLAYER_HEIGHT;

	_velX = 0;
	_velY = 0;

	_flip = SDL_FLIP_NONE;
}

void Player::move(SDL_Rect collision) {
	_posX += _velX;
	collider.x = _posX;
	
	if (_posX < 0 || _posX + PLAYER_WIDTH > WIDTH || checkCollision(collider, collision)) {
		_posX -= _velX;
		collider.x = _posX;
	}


	_posY += _velY;
	collider.y = _posY;
	
	if (_posY < 0 || _posY + PLAYER_HEIGHT > HEIGHT || checkCollision(collider, collision)) {
		_posY -= _velY;
		collider.y = _posY;
	}
}

void Player::move() {
	_posX += _velX;
	collider.x = _posX;

	if (_posX < 0 || _posX + PLAYER_WIDTH > WIDTH) {
		_posX -= _velX;
		collider.x = _posX;
	}


	_posY += _velY;
	collider.y = _posY;

	if (_posY < 0 || _posY + PLAYER_HEIGHT > HEIGHT) {
		_posY -= _velY;
		collider.y = _posY;
	}
}

void Player::handleEvent(SDL_Event& e, int& attackTime, int cooldown) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			
			case SDLK_UP: _velY -= PLAYER_VEL; 
			break;
			
			case SDLK_RIGHT: { 
				_velX += PLAYER_VEL;
				_flip = SDL_FLIP_NONE;
			}break;
			
			case SDLK_DOWN: _velY += PLAYER_VEL; 
			break;
			
			case SDLK_LEFT: { 
				_velX -= PLAYER_VEL; 
				_flip = SDL_FLIP_HORIZONTAL;
			}break;

			case SDLK_SPACE: {
				if (!cooldown) {
					attackTime = 8;
				}
			}break;
		}
	}
	else {
		if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
				case SDLK_UP: _velY += PLAYER_VEL; break;
				case SDLK_RIGHT: _velX -= PLAYER_VEL; break;
				case SDLK_DOWN: _velY -= PLAYER_VEL; break;
				case SDLK_LEFT: _velX += PLAYER_VEL; break;
			}
		}
	}
}

void Player::render(SDL_Renderer* renderer, Texture& texture) {
	texture.render(renderer, _posX, _posY, NULL, 0, NULL, _flip);
}

int Player::getPosX() {
	return this->_posX;
}

int Player::getPosY() {
	return this->_posY;
}

int Player::getVelX() {
	return this->_velX;
}

int Player::getVelY() {
	return this->_velY;
}

int Player::getCharacterHeight() {
	return PLAYER_HEIGHT;
}

int Player::getCharacterWidth() {
	return PLAYER_WIDTH;
}

SDL_Rect Player::getCollider() {
	return this->collider;
}

SDL_RendererFlip Player::getFlip() {
	return this->_flip;
}

void Player::setPosX(int x) {
	this->_posX = x;
}

void Player::setPosY(int y) {
	this->_posY = y;
}

void Player::setCollisionCoordinates(int x, int y) {
	this->collider.x = x;
	this->collider.y = y;
}

void Player::setCollider(SDL_Rect r) {
	this->collider = r;
}

void Player::setFlip(SDL_RendererFlip flip) {
	this->_flip = flip;
}

void Player::setVelX(int velX) {
	this->_velX = velX;
}

void Player::setVelY(int velY) {
	this->_velY = velY;
}