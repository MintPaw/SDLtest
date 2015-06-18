#include "mintSDL/system.h"
#include "game.h"

int gameMain(int argc, char* args[])
{
	MintSystem* sys = mint_SystemSetup(0);
	mint_SystemAddFont(sys, "assets/font/OpenSansRegular.ttf");
	sys->debugDraw = 1;

	sys->start = &gameLoop;

	mint_SystemInit(sys, 1);

	return 0;
}

void gameLoop(MintSystem* sys)
{
	for (;;)
	{
		mint_SystemUpdate(sys);
		mint_SystemDraw(sys);
	}
}