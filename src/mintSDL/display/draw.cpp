#include <SDL.h>
#include "mintSDL/system.h"
#include "mintSDL/display/draw.h"

void mint_DrawRect(MintSystem* sys, int x, int y, int width, int height, SDL_Color* colour)
{
	SDL_Rect rect = { x, y, width, height };

	SDL_SetRenderDrawColor(sys->sdlRenderer, colour->r, colour->g, colour->b, colour->a);
	SDL_RenderFillRect(sys->sdlRenderer, &rect);
}

void mint_DrawLine(MintSystem* sys, int x1, int y1, int x2, int y2, SDL_Color* colour)
{
	SDL_SetRenderDrawColor(sys->sdlRenderer, colour->r, colour->g, colour->b, colour->a);
	SDL_RenderDrawLine(sys->sdlRenderer, x1, y1, x2, y2);
}