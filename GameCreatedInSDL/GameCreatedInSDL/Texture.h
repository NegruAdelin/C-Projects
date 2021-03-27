#pragma once
#include "libs.h"

class Texture {
public:
	Texture(int width = 0, int height = 0, SDL_Texture* texture = NULL);
	virtual ~Texture();
	virtual bool loadFromFile(SDL_Renderer* renderer, std::string path);
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void free();
	int getWidth();
	int getHeight();
	SDL_Texture* getTexture();
	void setWidth(int width);
	void setHeight(int height);

protected:
	int _width, _height;
	SDL_Texture* _texture;

};