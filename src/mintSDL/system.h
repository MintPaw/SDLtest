#ifndef SYSTEM_H
#define SYSTEM_H

#define PRE_UPDATE 0
#define UPDATE 1
#define POST_UPDATE 2
#define PRE_DRAW 3
#define DRAW 4
#define POST_DRAW 5

#define MAX_TEXTURES 2048

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
	TTF_Font* font;
	SDL_Event event;
	MintTexture* textures[MAX_TEXTURES];
	char totalTextures;
	float elapsed;
	char stage;
	char quit;

	void (*start)(MintSystem* sys);
};

MintSystem* mint_SystemSetup();
char mint_SystemInit(MintSystem* sys);
void mint_SystemFullScreen(MintSystem* sys, char fullscreen);

void mint_SystemPreUpdate(MintSystem* sys);
void mint_SystemUpdate(MintSystem* sys);
void mint_SystemPostUpdate(MintSystem* sys);
void mint_SystemPreDraw(MintSystem* sys);
void mint_SystemDraw(MintSystem* sys);
void mint_SystemPostDraw(MintSystem* sys);

void mint_SystemAddTexture(MintSystem* sys, MintTexture* mintTexture);
void mint_SystemRemoveTexture(MintSystem* sys, MintTexture* mintTexture, char free);


#endif