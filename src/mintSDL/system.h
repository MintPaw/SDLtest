#ifndef SYSTEM_H
#define SYSTEM_H

struct MintSystem;

#include <SDL.h>
#include "mintSDL/util/input.h"
#include "mintSDL/util/timer.h"
#include "mintSDL/maths/phys.h"

struct MintSystem {
	SDL_Window* sdlWindow;
	SDL_Renderer* sdlRenderer;
	MintInput* input;
	MintFrameTimer* timer;
	MintPhysWorld* world;
	TTF_Font* fonts;
	SDL_Event event;
	char quit;

	void (*init)(MintSystem* sys);
	void (*preUpdate)(MintSystem* sys);
	void (*update)(MintSystem* sys);
	void (*postUpdate)(MintSystem* sys);
	void (*preDraw)(MintSystem* sys);
	void (*draw)(MintSystem* sys);
	void (*postDraw)(MintSystem* sys);
};

MintSystem* mint_SystemSetup();
char mint_SystemInit(MintSystem* sys);

#endif