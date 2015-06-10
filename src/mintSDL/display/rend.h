#ifndef IMAGE_H
#define IMAGE_H

struct MintRend;

#include <SDL.h>
#include "mintSDL/display/texture.h"

struct MintRend {
	MintTexture* mintTexture;
	SDL_Renderer* renderer;
	SDL_Rect* _clipRect;
	int _alpha;
};

SDL_Renderer* mint_RendCreateRenderer(SDL_Window* window, char vsync);
void mint_RendClearRenderer(SDL_Renderer* renderer);
SDL_Color* mint_RendHexToSDLColor(unsigned long colour);
unsigned long mint_RendSDLColorToHex(SDL_Color* sdlColor);

void mint_RendSetColour(MintRend* rend, SDL_Color* colour);
void mint_RendSetAlpha(MintRend* rend, char alpha);

#endif