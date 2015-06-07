#ifndef IMAGE_H
#define IMAGE_H

struct MintRend;

#include <SDL.h>
#include "texture.h"

struct MintRend {
	MintTexture* texture;
	SDL_Renderer* renderer;
	SDL_Rect* _clipRect;
	int _alpha;
};

SDL_Renderer* mint_DisplayCreateRenderer(SDL_Window* window, char vsync);
void mint_DisplayClearRenderer(SDL_Renderer* renderer);
SDL_Color* mint_DisplayHexToSDLColor(unsigned long colour);
unsigned long mint_DisplaySDLColorToHex(SDL_Color* sdlColor);

void mint_RendSetColour(MintRend* self, SDL_Color* colour);
void mint_RendSetAlpha(MintRend* self, char alpha);

#endif