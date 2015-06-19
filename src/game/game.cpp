#define _CRT_SECURE_NO_WARNINGS

#include "mintSDL/system.h"
#include "game/game.h"
#include "game/player.h"

#define MENU 1
#define GAME 2

MintSystem* _sys;
GameState* gameState;
int state = 0;

int gameMain(int argc, char* args[])
{
	_sys = mint_SystemSetup(0);
	mint_SystemAddFont(_sys, "assets/font/OpenSansRegular.ttf");
	_sys->debugDraw = 1;	

	_sys->start = &gameLoop;

	mint_SystemInit(_sys, 1);

	return 0;
}

void gameLoop(MintSystem* extraSys)
{
	startGame();
	for (;;)
	{
		if (state == GAME) updateGame();

		mint_SystemUpdate(_sys);
		mint_SystemDraw(_sys);
	}
}

void startGame()
{
	// mint_SystemFullScreen(_sys, 1);
	gameState = (GameState*)calloc(1, sizeof(GameState));
	gameState->players;
	gameState->totalPlayers = 0;

	state = GAME;

	{ // Setup tilemap
		// mint_TilemapCreate(_sys, "assets/img/tilemap.png", 64, 64, 0);
		// mint_TilemapGenerateFromTiled(_sys->tilemap, "assets/map/test1.tmx");
	}

	{ // Setup player
		Player* player = player_Setup(_sys);
		gameState->players[gameState->totalPlayers++] = player;

		mint_SystemAddTexture(_sys, player->mintTexture);

		mint_TextureSetX(player->mintTexture, 200);
		mint_TextureSetY(player->mintTexture, 200);
	}
}

void updateGame()
{
	int i;

	
	{ // Update players
		char left;
		char right;
		char up;
		char down;
		char animStr[99];

		for (i = 0; i < gameState->totalPlayers; i++)
		{
			strcpy(animStr, "");

			Player* player = gameState->players[i];
			MintTexture* texture = player->mintTexture;

			left = mint_InputCheckKey(_sys->input, SDL_SCANCODE_LEFT);
			right = mint_InputCheckKey(_sys->input, SDL_SCANCODE_RIGHT);
			up = mint_InputCheckKey(_sys->input, SDL_SCANCODE_UP);
			down = mint_InputCheckKey(_sys->input, SDL_SCANCODE_DOWN);

			if (left) mint_PhysSetVelocity(texture, -5, mint_PhysGetVelocity(texture).y);
			if (right) mint_PhysSetVelocity(texture, 5, mint_PhysGetVelocity(texture).y);
			if (up) mint_PhysSetVelocity(texture, mint_PhysGetVelocity(texture).x, -5);
			if (down) mint_PhysSetVelocity(texture, mint_PhysGetVelocity(texture).x, 5);

			strcpy(animStr, "player_blue_SMG_");

			if (up && right) {
				strcat(animStr, "upRight");
				texture->flip = SDL_FLIP_NONE;
			} else if (down && right) {
				strcat(animStr, "downRight");
				texture->flip = SDL_FLIP_NONE;
			} else if (up && left) {
				strcat(animStr, "upRight");
				texture->flip = SDL_FLIP_HORIZONTAL;
			} else if (down && left) {
				strcat(animStr, "downRight");
				texture->flip = SDL_FLIP_HORIZONTAL;
			} else if (left) {
				strcat(animStr, "right");
				texture->flip = SDL_FLIP_HORIZONTAL;
				player->dir4 = GEOM_LEFT;
			} else if (right) {
				strcat(animStr, "right");
				texture->flip = SDL_FLIP_NONE;
				player->dir4 = GEOM_RIGHT;
			} else if (up) {
				strcat(animStr, "up");
				texture->flip = SDL_FLIP_NONE;
				player->dir4 = GEOM_UP;
			} else if (down) {
				strcat(animStr, "down");
				texture->flip = SDL_FLIP_NONE;
				player->dir4 = GEOM_DOWN;
			} else {
				if (player->dir4 == GEOM_LEFT) {
					strcat(animStr, "right");
					texture->flip = SDL_FLIP_HORIZONTAL;
				} else {
					texture->flip = SDL_FLIP_NONE;
				}

				if (player->dir4 == GEOM_RIGHT) strcat(animStr, "right");
				if (player->dir4 == GEOM_UP) strcat(animStr, "up");
				if (player->dir4 == GEOM_DOWN) strcat(animStr, "down");
			}

			strcat(animStr, up || down || left || right ? "_running_" : "_standing_");

			mint_AnimPlay(mint_AnimGetByName(texture, animStr));
		}
	}
}