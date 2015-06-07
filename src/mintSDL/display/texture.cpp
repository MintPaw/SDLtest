#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "animation.h"
#include "texture.h"
#include "display.h"

int getWidth(MintTexture* self);
int getHeight(MintTexture* self);
void render(MintTexture* self);
void setColour(MintTexture* self, SDL_Color* colour);
void setAlpha(MintTexture* self, char alpha);
void setupAnimation(MintTexture* self, int totalAnimations);

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
	mintTexture->_alpha = NULL;
	mintTexture->x = 0;
	mintTexture->y = 0;
	mintTexture->getWidth = &getWidth;
	mintTexture->getHeight = &getHeight;
	mintTexture->setColour = &setColour;
	mintTexture->setAlpha = &setAlpha;
	mintTexture->setupAnimation = &setupAnimation;
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

void render(MintTexture* self)
{
	SDL_Rect quad = { self->x, self->y, self->getWidth(self), self->getHeight(self) };
	SDL_RenderCopy(self->renderer, self->texture, NULL, &quad);
}

void setColour(MintTexture* self, SDL_Color* colour)
{
	SDL_SetTextureColorMod(self->texture, colour->r, colour->g, colour->b);
}

void setAlpha(MintTexture* self, char alpha)
{
	if (self->_alpha == NULL) SDL_SetTextureBlendMode(self->texture, SDL_BLENDMODE_BLEND);

	self->_alpha = alpha;
	SDL_SetTextureAlphaMod(self->texture, self->_alpha);
}

void setupAnimation(MintTexture* self, int totalAnims)
{
	self->_totalAnims = 0;
	self->anims = (MintAnimation*)malloc(sizeof(MintAnimation) * totalAnims);
}