const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 832;

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "mintSDL/system.h"
#include "mintSDL/util/input.h"
#include "mintSDL/util/timer.h"
#include "mintSDL/maths/phys.h"

void _updateLoop(MintSystem* sys);
void _close(MintSystem* sys);

MintSystem* mint_SystemSetup()
{
	MintSystem* sys = (MintSystem*)malloc(sizeof(MintSystem));
	sys->sdlWindow = NULL;
	sys->sdlRenderer = NULL;
	sys->input = NULL;
	sys->timer = NULL;
	sys->world = NULL;
	sys->fonts = NULL;
	sys->quit = 0;
	sys->elapsed = 0;

	sys->start = NULL;

	return sys;
}

char mint_SystemInit(MintSystem* sys)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to init SDL_ERROR: %s\n", SDL_GetError());
		return 0;
	} else {
		sys->sdlWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (sys->sdlWindow == NULL) {
			printf("Failed to create window SDL_ERROR: %s\n", SDL_GetError());
			return 0;
		} else {
			// TODO(jeru): Vsync option
			sys->sdlRenderer = mint_RendCreateSdlRenderer(sys->sdlWindow, 1);
		}
	}

	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 0;
	}

	if(TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 0;
	}

	sys->input = mint_InputSetup();
	sys->timer = mint_TimerSetup();
	sys->world = mint_PhysSetupWorld(0, 10);

	SDL_UpdateWindowSurface(sys->sdlWindow);

	sys->start(sys);

	//- ttfOpenSans = TTF_OpenFont("assets/font/OpenSansRegular.ttf", 28);

	return 1;
}

void mint_SystemPreUpdate(MintSystem* sys)
{
	{ // Handle Events
		while (SDL_PollEvent(&sys->event) != 0) {
			if (sys->event.type == SDL_KEYDOWN || sys->event.type == SDL_KEYUP) mint_InputUpdate(sys->input, &sys->event);
			if (sys->event.type == SDL_QUIT || mint_InputCheckKey(sys->input, SDL_SCANCODE_ESCAPE)) sys->quit = 1;
		}
	}
}

void mint_SystemUpdate(MintSystem* sys)
{
	mint_TimerUpdate(sys->timer, (float)(SDL_GetTicks() / 1000.0));
	sys->elapsed = sys->timer->elapsed;
}

void mint_SystemPostUpdate(MintSystem* sys)
{

}

void mint_SystemPreDraw(MintSystem* sys)
{
	mint_RendClearSdlRenderer(sys->sdlRenderer);
}

void mint_SystemDraw(MintSystem* sys)
{

}

void mint_SystemPostDraw(MintSystem* sys)
{
	SDL_RenderPresent(sys->sdlRenderer);


	if (sys->quit) _close(sys);
}

void _close(MintSystem* sys)
{
	SDL_DestroyWindow(sys->sdlWindow);
	SDL_DestroyRenderer(sys->sdlRenderer);
	sys->sdlWindow = NULL;

	mint_InputFree(sys->input);
	mint_TimerFree(sys->timer);
	mint_PhysFreeWorld(sys->world);
	free(sys);
	// TTF_CloseFont(ttfOpenSans);

	SDL_Quit();

#ifdef _CRTDBG_MAP_ALLOC
	_CrtDumpMemoryLeaks();
#endif
	exit(0);
}