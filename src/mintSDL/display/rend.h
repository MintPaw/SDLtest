#ifndef IMAGE_H
#define IMAGE_H

struct MintRend;

#include <SDL.h>
#include "mintSDL/display/texture.h"

struct MintRend {
	MintTexture* mintTexture;
	SDL_Renderer* renderer;
	unsigned char _alpha;
};

SDL_Renderer* mint_RendCreateSdlRenderer(SDL_Window* window, char vsync);
void mint_RendFullScreen(SDL_Window* sdlWindow, char fullscreen);
void mint_RendClearSdlRenderer(SDL_Renderer* renderer);
void mint_RendHexToSDLColor(unsigned long colour, SDL_Color* sdlColour);
unsigned long mint_RendSDLColorToHex(SDL_Color* sdlColor);

// void mint_RendSetColour(MintRend* rend, SDL_Color* colour);
// void mint_RendSetAlpha(MintRend* rend, char alpha);
// void mint_RendFree(MintRend* rend);

#endif