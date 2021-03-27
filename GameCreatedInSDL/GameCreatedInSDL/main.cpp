#include "libs.h"



int main(int argc, char* args[]) {
	srand(time(NULL));
	ThreadData* data = NULL;
	short int score = 0;
	int attackSpeed = 0;
	SDL_Window* window = NULL;
	SDL_Renderer* render = NULL;
	Texture playerTexture, enemyTexture;
	Texture appleTexture;
	Texture background;
	Texture weaponTexture;
	FontTexture font;
	Weapon sword;
	Dot apple;
	SDL_Event e;
	int attackTime = 0;
	
	bool dead = false;
	SDL_Thread* createEnemy = NULL;
	SDL_Thread* moveEnemy = NULL;

	if (!init(window, render)) {
		
		printf("Initialization failed");
	
	}
	else if (!loadMedia<Texture>(render, playerTexture, "./materials/finn.png") ||
		!loadMedia<Texture>(render, appleTexture, "./materials/apple.png") ||
		!loadMedia<Texture>(render, background, "./materials/background.png") ||
		!loadMedia<Texture>(render, weaponTexture, "./materials/another_sword.png") ||
		!loadMedia<Texture>(render, enemyTexture, "./materials/Lemongrab.png") ||
		!loadMedia<FontTexture>(render, font, "Score: 0")) {

			printf("Failed to load media");
	}
	else {
		font.setWidth(140);
		font.setHeight(60);

		createEnemy = SDL_CreateThread(threadFunction, "AThread", (void*)data);
		moveEnemy = SDL_CreateThread(threadFunctionMoveEnemy, "Move Thread", (void*)data);
		
		while (!quit) {
			
			while (SDL_PollEvent(&e) != 0) {
				
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				player->handleEvent(e, attackTime, attackSpeed);
			
			}

			player->move();
			SDL_Rect playerPos = player->getCollider();
			

			if (player->getFlip() == SDL_FLIP_HORIZONTAL) {
				
				sword.setPosX(player->getPosX() - 20);
				sword.setPosY(player->getPosY() - 14);
			
			}
			else {
				
				sword.setPosX(player->getPosX());
				sword.setPosY(player->getPosY() - 14);

			}

			if (checkCollision(player->getCollider(), apple.getCollider())) {
				
				apple.generatePosition(player);
				score++;
				font.setText(render, "Score: " + std::to_string(score));
			}

			SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(render);

			SDL_RenderCopy(render, background.getTexture(), NULL, NULL);

			if (attackTime) {
				
				weaponTexture.render(render,
					player->getPosX() - 46 + (player->getFlip() * 15),
					player->getPosY() - 15,
					NULL,
					0.0,
					NULL,
					player->getFlip());

				if (attackSpeed == 0) {
					
					attackSpeed = sword.getAttackSpeed();
					
					std::vector<Character*>::iterator it = enemies.begin();
					for (auto enemy : enemies) {
						if (checkCollision(sword.getCollider(), enemy->getCollider())) {
							enemies.erase(it);
							break;
						}
						else {
							it++;
						}
					}
				}

				attackTime--;
			
			}

			if (attackSpeed) {

				attackSpeed--;

			}

			for (auto enemy : enemies) {
				if (checkCollision(player->getCollider(), enemy->getCollider())) {

					player->setPosX(0);
					player->setPosY(0);
					enemy->setPosX(rand() % (WIDTH - enemy->getCharacterWidth() - SPAWN_RANGE) + SPAWN_RANGE);
					enemy->setPosY(rand() % (HEIGHT - enemy->getCharacterHeight() - SPAWN_RANGE) + SPAWN_RANGE);
					enemy->setCollisionCoordinates(enemy->getPosX(),
						enemy->getPosY());
					score = 0;
					font.setText(render, "Score: " + std::to_string(score));

					//All for Die Message
					TTF_Font* dieFont = TTF_OpenFont("./materials/AtariClassic-gry3.ttf", 60);
					SDL_Surface* dieSurface = TTF_RenderText_Solid(dieFont, "You Died", SDL_Color{ 236, 25, 25, 200 });
					SDL_Texture* dieTexture = SDL_CreateTextureFromSurface(render, dieSurface);

					SDL_FreeSurface(dieSurface);
					dieSurface = NULL;

					SDL_Rect* dieMsgRectangle = new SDL_Rect{ WIDTH / 2 - 80, HEIGHT / 2 - 40, 160, 80 };
					SDL_RenderCopy(render, dieTexture, NULL, dieMsgRectangle);

					SDL_DestroyTexture(dieTexture);
					dieTexture = NULL;

					TTF_CloseFont(dieFont);
					dieFont = NULL;
					//END
					enemies.clear();
					dead = true;
				}
			}

			player->render(render, playerTexture);
			for (auto it : enemies) {
				it->render(render, enemyTexture);
			}
			apple.render(render, appleTexture);
			font.render(render, 5, 5);

			SDL_RenderPresent(render);
			
			if (dead) {
				dead = false;
				SDL_Delay(2000);
			}
		}
		
		SDL_WaitThread(createEnemy, NULL);
	}

	close(render, window, playerTexture, appleTexture, weaponTexture, enemyTexture);
	delete player;
	player = NULL;
	return 0;

}
