#include <SDL.h>
#include "display.h"
#include "draw.h"

void mint_DrawRect(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color* colour)
{
	SDL_Rect rect = { x, y, width, height };

	SDL_SetRenderDrawColor(renderer, colour->r, colour->g, colour->b, colour->a);
	SDL_RenderFillRect(renderer, &rect);
}

void mint_DrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color* colour)
{
	SDL_SetRenderDrawColor(renderer, colour->r, colour->g, colour->b, colour->a);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}