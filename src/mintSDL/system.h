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

	void (*start)(MintSystem* sys);
};

MintSystem* mint_SystemSetup();
char mint_SystemInit(MintSystem* sys);

void mint_SystemPreUpdate(MintSystem* sys);
void mint_SystemUpdate(MintSystem* sys);
void mint_SystemPostUpdate(MintSystem* sys);
void mint_SystemPreDraw(MintSystem* sys);
void mint_SystemDraw(MintSystem* sys);
void mint_SystemPostDraw(MintSystem* sys);


#endif