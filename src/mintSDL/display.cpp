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
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
}