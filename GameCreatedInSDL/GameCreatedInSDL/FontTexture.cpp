#include "libs.h"

FontTexture::~FontTexture() {

	_fontSize = 0;
	_fontPath = "";
}

bool FontTexture::loadFromFile(SDL_Renderer* renderer, std::string text) {
	
	TTF_Font* font = TTF_OpenFont(_fontPath.c_str(), _fontSize);
	if (font == NULL) {
		printf("An error occurred  at load font! SDL_Erorr: %s\n", TTF_GetError());
		return false;
	}
	else {
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), _color);
		_texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_FreeSurface(surface);
		surface = NULL;
	}

	TTF_CloseFont(font);
	font = NULL;
	
	return (_texture != NULL);
}

void FontTexture::setText(SDL_Renderer* renderer, std::string text) {

	TTF_Font* font = TTF_OpenFont(_fontPath.c_str(), _fontSize);
	if (font == NULL) {
		printf("An error occurred  at load font! SDL_Erorr: %s\n", TTF_GetError());
	}
	else {
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), _color);
		_texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_FreeSurface(surface);
		surface = NULL;
	}

	TTF_CloseFont(font);
	font = NULL;
}

void FontTexture::setColor(SDL_Color color) {
	_color = color;
}

void FontTexture::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	_color = { r, g, b, a };
}

void FontTexture::setFontSize(int fontSize) {
	_fontSize = fontSize;
}

void FontTexture::setFontPath(std::string fontPath) {
	_fontPath = fontPath;
}