#ifndef GAME_H
#define GAME_H

struct GameState;

#include "mintSDL/system.h"
#include "game/player.h"

struct GameState {
	Player* players[4];
	char totalPlayers;
};

int gameMain(int argc, char* args[]);
void gameLoop(MintSystem* sys);
void startGame();
void updateGame();

#endif