const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 832;

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "mintSDL/system.h"
#include "mintSDL/util/input.h"
#include "mintSDL/util/timer.h"
#include "mintSDL/maths/phys.h"

void _updateLoop(MintSystem* sys);
void _preUpdate(MintSystem* sys);
void _update(MintSystem* sys);
void _postUpdate(MintSystem* sys);
void _preDraw(MintSystem* sys);
void _draw(MintSystem* sys);
void _postDraw(MintSystem* sys);
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
	sys->init = NULL;
	
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

	SDL_UpdateWindowSurface(sys->sdlWindow);

	//- ttfOpenSans = TTF_OpenFont("assets/font/OpenSansRegular.ttf", 28);

	return 1;
}

void _updateLoop(MintSystem* sys)
{
	while (!sys->quit) {
		_preUpdate(sys);
		_update(sys);
		_postUpdate(sys);
		_preDraw(sys);
		_draw(sys);
		_postDraw(sys);
	}
}

void _preUpdate(MintSystem* sys)
{
	{ // Handle Events
		SDL_Event* e = NULL;
		while (SDL_PollEvent(e) != 0) {
			// if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			// if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;
		}
	}
}

void _update(MintSystem* sys)
{

}

void _postUpdate(MintSystem* sys)
{

}

void _preDraw(MintSystem* sys)
{
	mint_RendClearSdlRenderer(sys->sdlRenderer);
}

void _draw(MintSystem* sys)
{

}

void _postDraw(MintSystem* sys)
{
	SDL_RenderPresent(sys->sdlRenderer);
}

void _close(MintSystem* sys)
{
	SDL_DestroyWindow(sys->sdlWindow);
	SDL_DestroyRenderer(sys->sdlRenderer);
	sys->sdlWindow = NULL;

	// mint_InputFree(input);
	// mint_TimerFree(timer);
	// mint_PhysFreeWorld(world);
	// TTF_CloseFont(ttfOpenSans);

	SDL_Quit();
}