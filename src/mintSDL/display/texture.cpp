#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

char mint_DisplayTextureSetup()
{
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 0;
	}

	return 1;
}

SDL_Texture* mint_DisplayTextureLoadPNG(SDL_Renderer* renderer, char* path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL) {
		printf("Failed to create surface from %s, SDL_Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		printf("Failed to create texture from %s, SDL_Error: %s\n", path, SDL_GetError());
	}

	SDL_FreeSurface(surface);

	return texture;
}