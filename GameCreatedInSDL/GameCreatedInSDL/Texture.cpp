#include "libs.h"

Texture::Texture(int width, int height, SDL_Texture* texture) {
	
	_width = width;
	_height = height;
	_texture = texture;

}

void Texture::free() {
	
	if (_texture != NULL) {
		_width = 0;
		_height = 0;
		SDL_DestroyTexture(_texture);
		_texture = NULL;
	}

}

Texture::~Texture() {
	free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, std::string path) {
	
	free();

	SDL_Surface* surface = IMG_Load(path.c_str());
	
	if (surface == NULL) {
		printf("Unable to load image %s! SDL_Image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

		_texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (_texture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
		}
		else {
			_width = surface->w;
			_height = surface->h;
		}

		SDL_FreeSurface(surface);
	}

	return _texture != NULL;

}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip,
	double angle, SDL_Point* center,
	SDL_RendererFlip flip) {

	SDL_Rect rect = { x, y, _width, _height };

	if (clip != NULL) {
		rect.w = clip->w;
		rect.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, _texture, clip, &rect, angle, center, flip);

}

int Texture::getWidth() {
	return _width;
}

int Texture::getHeight() {
	return _height;
}

SDL_Texture* Texture::getTexture() {
	return _texture;
}

void Texture::setHeight(int height) {
	_height = height;
}

void Texture::setWidth(int width){
	_width = width;
}