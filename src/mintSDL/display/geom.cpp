#include <SDL.h>
#include "display.h"
#include "geom.h"

void mint_GeomDrawRect(SDL_Renderer* renderer, int x, int y, int width, int height, unsigned long colour)
{
	SDL_Rect rect = { x, y, width, height };
	SDL_Color sdlColor;
	mint_DisplayHexToSDLColor(&sdlColor, colour);

	SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
	SDL_RenderFillRect(renderer, &rect);
}

void mint_GeomDrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, unsigned long colour)
{
	SDL_Color sdlColor;
	mint_DisplayHexToSDLColor(&sdlColor, colour);

	SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}