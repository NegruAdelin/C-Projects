#include "libs.h"


bool checkCollision(SDL_Rect a, SDL_Rect b) {

	int ALeft, BLeft;
	int ARight, BRight;
	int ATop, BTop;
	int ABottom, BBottom;

	ALeft = a.x;
	BLeft = b.x;
	ARight = a.x + a.w;
	BRight = b.x + b.w;

	ATop = a.y;
	BTop = b.y;
	ABottom = a.y + a.h;
	BBottom = b.y + b.h;

	if (ATop >= BBottom) {
		return false;
	}

	if (ABottom <= BTop) {
		return false;
	}

	if (ALeft >= BRight) {
		return false;
	}

	if (ARight <= BLeft) {
		return false;
	}

	return true;

}

bool init(SDL_Window*& window, SDL_Renderer*& render) {

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() == -1) {
		printf("Error occured at video init %s\n", SDL_GetError());
		success = false;
	}
	else {

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		window = SDL_CreateWindow("Finn and Apple Hunting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (render == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;

}

void close(SDL_Renderer*& renderer, SDL_Window*& window, Texture& player, Texture& apple, Texture& weapon, Texture& enemy) {
	
	player.free();
	apple.free();
	weapon.free();
	enemy.free();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	renderer = NULL;
	window = NULL;
	weapon = NULL;
	enemy = NULL;

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

void generatePosEnemy(Character*& enemy) {
	do {

		enemy->setPosX(rand() % (WIDTH - enemy->getCharacterWidth()));
		enemy->setPosY(rand() % (HEIGHT - enemy->getCharacterHeight()));
		enemy->setCollisionCoordinates(enemy->getPosX(), enemy->getPosY());

	} while (abs(enemy->getPosX() - player->getPosX()) <= SPAWN_RANGE &&
		abs(enemy->getPosY() - player->getPosY()) <= SPAWN_RANGE);
}

int threadFunction(void* data) {
	
	while(!quit){
		
		if (enemies.size() < 10) {
			Character* c = new Enemy;
			do {

				c->setPosX(rand() % (WIDTH - c->getCharacterWidth()));
				c->setPosY(rand() % (HEIGHT - c->getCharacterHeight()));
				c->setCollisionCoordinates(c->getPosX(), c->getPosY());

			} while (abs(c->getPosX() - player->getPosX()) <= SPAWN_RANGE &&
				abs(c->getPosY() - player->getPosY()) <= SPAWN_RANGE);

			enemies.push_back(c);
			c = NULL;
		}

		SDL_Delay(2000);
	}

	return 0;

}

int threadFunctionMoveEnemy(void* data) {

	while (!quit) {
		if (!enemies.empty()) {
			for (auto it : enemies) {
				it->move(player->getCollider());
			}
			SDL_Delay(20);
		}
	}

	return 0;

}