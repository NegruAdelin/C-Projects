#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <mutex>
#include <vector>
#include <string>
#include <iostream>
#include <SDL_ttf.h>
#include <cmath>
#include "Texture.h"
#include "Character.h"
#include "Enemy.h"
#include "Player.h"
#include "Dot.h"
#include "Weapon.h"
#include "FontTexture.h"

typedef struct ThreadData {
	SDL_Renderer* render;
	Texture text;
};

extern const int WIDTH = 900;
extern const int HEIGHT = 600;
extern const int SPAWN_RANGE = 100;
bool quit = false;
std::vector<Character*> enemies;
Character* player = new Player;
std::mutex vectorMutex;

/**
*	\brief checkCollision verify if 2 rectangles are in a collision
*	\return TRUE if the rectangles are in collision, FALSE if are not
*/
bool checkCollision(SDL_Rect a, SDL_Rect b);
bool init(SDL_Window*& window, SDL_Renderer*& render);
void close(SDL_Renderer*& renderer, SDL_Window*& window, Texture& player, Texture& apple, Texture& weapon, Texture& enemy);
void generatePosEnemy(Character*& enemy);

int threadFunction(void* data);
int threadFunctionMoveEnemy(void* data);

template <class T>
bool loadMedia(SDL_Renderer* renderer, T& texture, std::string path)
{
	bool success = true;

	if (!texture.loadFromFile(renderer, path))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	return success;
}