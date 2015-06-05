#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "display.h"

SDL_Renderer* mint_DisplayCreateRenderer(SDL_Window* window)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Failed to create renderer, SDL_Error: \n", SDL_GetError());
	}

	return renderer;
}

void mint_DisplayClearRenderer(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}

SDL_Color* mint_DisplayHexToSDLColor(unsigned long colour)
{
	SDL_Color *sdlColor = (SDL_Color*)malloc(sizeof(SDL_Color));
	sdlColor->r = ((colour >> 32) & 0xFF);
	sdlColor->g = ((colour >> 16) & 0xFF);
	sdlColor->b = ((colour >> 8) & 0xFF);
	sdlColor->a = (colour & 0xFF);

	return sdlColor;
}

unsigned long mint_DisplayToSDLColorHex(SDL_Color* sdlColor)
{   
    return (((sdlColor->a & 0xff) << 32) + ((sdlColor->r & 0xff) << 16) + ((sdlColor->g & 0xff) << 8) + (sdlColor->b & 0xff));
}