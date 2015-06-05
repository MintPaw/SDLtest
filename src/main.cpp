#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>
#include <string>
#include "mintSDL\input.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

char init();
void close();

//The window we'll be rendering to
SDL_Window* sdlWindow = NULL;
    
//The surface contained by the window
SDL_Surface* sdlScreenSurface = NULL;

int main(int argc, char* args[])
{
	init();

	SDL_UpdateWindowSurface(sdlWindow);

	SDL_Event e;
	InputSetup *input = mint_InputSetup();
	char quit = 0;

	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) quit = 1;

			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
				mint_InputUpdate(input, &e.key);
			}

			// printf("SDL_SCANCODE_A is %d\n", mint_InputCheckStatus(input, SDL_SCANCODE_A));
			// printf("Key: %s", SDL_GetKeyName(e.key.keysym.sym));
		}
	}

	close();

	return 0;
}

char init()
{
	char success = 1;

	// Init
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to init SDL_ERROR: %s\n", SDL_GetError());
		success = 0;
	} else {
		// Create window
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
			// Get surface
			sdlScreenSurface = SDL_GetWindowSurface(sdlWindow);
		}
	}

	return success;
}

void close()
{
	SDL_DestroyWindow(sdlWindow);
	sdlWindow = NULL;

	SDL_Quit();
}