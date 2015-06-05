#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "display.h"

int getWidth(MintTexture* self);
int getHeight(MintTexture* self);
void render(MintTexture* self, int x, int y);

char mint_DisplayTextureSetup()
{
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 0;
	}

	return 1;
}

MintTexture* mint_DisplayTextureFromPNG(SDL_Renderer* renderer, char* path)
{
	MintTexture* mintTexture = (MintTexture*)malloc(sizeof(mintTexture));
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL) {
		printf("Failed to create surface from %s, SDL_Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	mintTexture->texture = SDL_CreateTextureFromSurface(renderer, surface);
	mintTexture->renderer = renderer;
	mintTexture->_width = surface->w;
	mintTexture->_height = surface->h;
	mintTexture->getWidth = &getWidth;
	mintTexture->getHeight = &getHeight;
	mintTexture->render = &render;

	if (mintTexture->texture == NULL) {
		printf("Failed to create texture from %s, SDL_Error: %s\n", path, SDL_GetError());
	}

	SDL_FreeSurface(surface);

	return mintTexture;
}

int getWidth(MintTexture* self)
{
	return self->_width;
}

int getHeight(MintTexture* self)
{
	return self->_height;
}

void render(MintTexture* self, int x, int y)
{
	SDL_Rect quad = { x, y, self->getWidth(self), self->getHeight(self) };
	SDL_RenderCopy(self->renderer, self->texture, NULL, &quad);
}

void setColor(MintTexture* self, unsigned long colour)
{
	//mint_DisplayHexToSDLColor()
	//SDL_SetTextureColorMod( mTexture, red, green, blue );
}