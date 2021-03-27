#pragma once
#include "libs.h"

class FontTexture : public Texture {
public:
	FontTexture(int width = 0, int height = 0, SDL_Texture* texture = NULL, SDL_Color color = { 255, 255, 255, 155 }, int fontSize = 50, std::string fontPath = "./materials/AtariClassic-gry3.ttf") : Texture(width, height, texture), _color(color), _fontSize(fontSize), _fontPath(fontPath) {};
	~FontTexture();
	bool loadFromFile(SDL_Renderer* renderer, std::string path);
	void setText(SDL_Renderer* renderer, std::string text);
	
	void setColor(SDL_Color color);
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 155);
	void setFontSize(int fontSize);
	void setFontPath(std::string fontPath);

protected:
	SDL_Color _color;
	int _fontSize;
	std::string _fontPath;
};