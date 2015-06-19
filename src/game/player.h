#ifndef PLAYER_H
#define PLAYER_H

struct Player;

#include "mintSDL/display/texture.h"

struct Player {
	MintTexture* mintTexture;
	char dir4;
};

Player* player_Setup(MintSystem* _sys);

#endif