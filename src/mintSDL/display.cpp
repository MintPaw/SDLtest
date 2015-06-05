#include <stdio.h>
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

void mint_DisplayDrawRect(SDL_Renderer* renderer, int x, int y, int width, int height, unsigned long colour)
{
	SDL_Rect rect = { x, y, width, height };
	SDL_Color sdlColor;
	mint_DisplayHexToSDLColor(&sdlColor, colour);

	SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
	SDL_RenderFillRect(renderer, &rect);
}

void mint_DisplayDrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, unsigned long colour)
{
	SDL_Color sdlColor;
	mint_DisplayHexToSDLColor(&sdlColor, colour);

	SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void mint_DisplayHexToSDLColor(SDL_Color* sdlColor, unsigned long colour)
{
	sdlColor->r = ((colour >> 32) & 0xFF);
	sdlColor->g = ((colour >> 16) & 0xFF);
	sdlColor->b = ((colour >> 8) & 0xFF);
	sdlColor->a = (colour & 0xFF);
}
