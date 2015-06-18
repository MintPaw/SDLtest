#include "mintSDL/system.h"
#include "game/game.h"
#include "game/player.h"

#define MENU 1
#define GAME 2

MintSystem* _sys;
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
		mint_SystemUpdate(_sys);
		mint_SystemDraw(_sys);
	}
}

void startGame()
{
	// mint_SystemFullScreen(_sys, 1);
	state = GAME;

	{ // Setup tilemap
		mint_TilemapCreate(_sys, "assets/img/tilemap.png", 64, 64, 0);
		mint_TilemapGenerateFromTiled(_sys->tilemap, "assets/map/test1.tmx");
	}

	{ // Setup player
		// char left;
		// char right;
		// char up;
		// char down;

		// char animStr[99];
		// char dirStr = GEOM_RIGHT;

		MintTexture* player = player_Setup(_sys);

		mint_TextureSetX(player, 200);
		mint_TextureSetY(player, 200);
	}
}