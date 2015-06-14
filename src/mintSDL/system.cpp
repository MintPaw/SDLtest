#include <SDL.h>
#include <stdio.h>
#include "mintSDL/util/system.h"

MintSystem* mint_SystemSetup()
{
	MintSystem* sys = (MintSystem*)malloc(sizeof(MintSystem));
}

char mint_SystemInit(MintSystem* sys)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to init SDL_ERROR: %s\n", SDL_GetError());
	} else {
		sys->sdlWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (sys->sdlWindow == NULL) {
			printf("Failed to create window SDL_ERROR: %s\n", SDL_GetError());
		} else {
			// TODO(jeru): Vsync option
			sys->sdlRenderer = mint_RendCreateSdlRenderer(sys->sdlWindow, 1);
		}
	}

	return 1;
}

void mint_SystemUpdate()
{

}