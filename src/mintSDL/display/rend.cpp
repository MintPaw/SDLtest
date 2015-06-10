#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "mintSDL/display/rend.h"

SDL_Renderer* mint_RendCreateSdlRenderer(SDL_Window* window, char vsync)
{
	SDL_Renderer* renderer;
	if (vsync)
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	} else {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
	if (renderer == NULL) {
		printf("Failed to create renderer, SDL_Error: \n", SDL_GetError());
	}

	return renderer;
}

void mint_RendClearSdlRenderer(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}

void mint_RendHexToSDLColor(unsigned long colour, SDL_Color* sdlColor)
{
	sdlColor->r = ((colour >> 24) & 0xFF);
	sdlColor->g = ((colour >> 16) & 0xFF);
	sdlColor->b = ((colour >> 8) & 0xFF);
	sdlColor->a = (colour & 0xFF);
}

unsigned long mint_RendSDLColorToHex(SDL_Color* sdlColor)
{
		return (((sdlColor->r & 0xFF) << 24) + ((sdlColor->g & 0xFF) << 16) + ((sdlColor->b & 0xFF) << 8) + (sdlColor->a & 0xFF));
}

MintRend* mint_RendSetup(MintTexture* mintTexture, SDL_Renderer* renderer)
{
	MintRend* rend = (MintRend*)malloc(sizeof(MintRend));

	rend->mintTexture = mintTexture;
	rend->renderer = renderer;
	rend->_alpha = 255;
	rend->_clipRect = NULL;

	return rend;
}

void mint_RendSetColour(MintRend* rend, SDL_Color* colour)
{
	SDL_SetTextureColorMod(rend->mintTexture->texture, colour->r, colour->g, colour->b);
}

void mint_RendSetAlpha(MintRend* rend, char alpha)
{
	if (rend->_alpha == NULL) SDL_SetTextureBlendMode(rend->mintTexture->texture, SDL_BLENDMODE_BLEND);

	rend->_alpha = alpha;
	SDL_SetTextureAlphaMod(rend->mintTexture->texture, rend->_alpha);
}

void mint_RendFree(MintRend* rend)
{
	free(rend);
	rend = NULL;
}