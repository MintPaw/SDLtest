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
	sdlColor->r = ((colour >> 24) & 0xFF);
	sdlColor->g = ((colour >> 16) & 0xFF);
	sdlColor->b = ((colour >> 8) & 0xFF);
	sdlColor->a = (colour & 0xFF);

	return sdlColor;
}

unsigned long mint_DisplaySDLColorToHex(SDL_Color* sdlColor)
{   
    return (((sdlColor->r & 0xFF) << 24) + ((sdlColor->g & 0xFF) << 16) + ((sdlColor->b & 0xFF) << 8) + (sdlColor->a & 0xFF));
}