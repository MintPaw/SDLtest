#include <SDL.h>
#include <stdio.h>
#include "mintSDL\input\input.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

char init();
char loadMedia();
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

int main(int argc, char* args[])
{
	init();
	loadMedia();

	SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);

	SDL_Event e;
	char quit = 0;

	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) quit = 1;

			if (e.key) {
				update
			}
			// printf("Key: %s", SDL_GetKeyName(e.key.keysym.sym));
			// printf("\t\tUnicode: %d\n", e.key.keysym.sym);
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
		gWindow = SDL_CreateWindow("SDL Test",
		                           SDL_WINDOWPOS_UNDEFINED,
		                           SDL_WINDOWPOS_UNDEFINED,
		                           SCREEN_WIDTH,
		                           SCREEN_HEIGHT,
		                           SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Failed to create window SDL_ERROR: %s\n", SDL_GetError());
			success = 0;
		} else {
			// Get surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

char loadMedia()
{
	char success = 1;

	// Load splash
	gHelloWorld = SDL_LoadBMP("splash.bmp");

	if (gHelloWorld == NULL) {
		printf("Failed to load image: %s\n", SDL_GetError());
		success = 0;
	}

	return success;
}

void close()
{
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}