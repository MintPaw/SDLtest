#include <SDL.h>
#include <stdio.h>
#include <string>
#include "mintSDL\input.h"
#include "mintSDL\display\display.h"
#include "mintSDL\display\geom.h"
#include "mintSDL\display\texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

char init();
void close();

/*
	Todo:
		
*/

SDL_Window* sdlWindow = NULL;
SDL_Surface* sdlScreenSurface = NULL;
SDL_Renderer* sdlRenderer = NULL;

int main(int argc, char* args[])
{
	init();

	SDL_UpdateWindowSurface(sdlWindow);

	SDL_Event e;
	InputSetup *input = mint_InputSetup();
	char quit = 0;

	MintTexture texture = *mint_DisplayTextureFromPNG(sdlRenderer, "pngSplash.png");
	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
				mint_InputUpdate(input, &e.key);
			}

			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);
			
			texture.render(&texture, 0, 0);

			SDL_UpdateWindowSurface(sdlWindow);
			SDL_RenderPresent(sdlRenderer);
		}
	}

	close();

	return 0;
}

char init()
{
	char success = 1;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to init SDL_ERROR: %s\n", SDL_GetError());
		success = 0;
	} else {
		sdlWindow = SDL_CreateWindow("SDL Test",
		                             SDL_WINDOWPOS_UNDEFINED,
		                             SDL_WINDOWPOS_UNDEFINED,
		                             SCREEN_WIDTH,
		                             SCREEN_HEIGHT,
		                             SDL_WINDOW_SHOWN);
		if (sdlWindow == NULL) {
			printf("Failed to create window SDL_ERROR: %s\n", SDL_GetError());
			success = 0;
		} else {
			sdlScreenSurface = SDL_GetWindowSurface(sdlWindow);
			sdlRenderer = mint_DisplayCreateRenderer(sdlWindow);
		}
	}

	return success;
}

void close()
{
	SDL_DestroyWindow(sdlWindow);
	SDL_DestroyRenderer(sdlRenderer);
	sdlWindow = NULL;

	SDL_Quit();
}