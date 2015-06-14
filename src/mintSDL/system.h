#ifndef SYSTEM_H
#define SYSTEM_H

struct MintSystem;

#include <SDL.h>

struct MintSystem {
	SDL_Window* sdlWindow;
	SDL_Renderer* sdlRenderer;
};

MintSystem* mint_SystemSetup();
char mint_SystemInit(MintSystem* sys);
void mint_SystemUpdate();

#endif