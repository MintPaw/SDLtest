#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "anim.h"
#include "texture.h"
#include "display.h"

char mint_TextureSetup()
{
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 0;
	}

	return 1;
}

MintTexture* mint_TextureFromPNG(SDL_Renderer* renderer, char* path)
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

	if (mintTexture->texture == NULL) {
		printf("Failed to create texture from %s, SDL_Error: %s\n", path, SDL_GetError());
	}

	SDL_FreeSurface(surface);

	return mintTexture;
}

int mint_TextureGetWidth(MintTexture* self)
{
	return self->_width;
}

int mint_TextureGetHeight(MintTexture* self)
{
	return self->_height;
}

void mint_TextureRender(MintTexture* self)
{
	SDL_Rect quad = { self->x, self->y, mint_TextureGetWidth(self), mint_TextureGetHeight(self) };
	SDL_RenderCopy(self->renderer, self->texture, NULL, &quad);
}

void mint_TextureSetColour(MintTexture* self, SDL_Color* colour)
{
	SDL_SetTextureColorMod(self->texture, colour->r, colour->g, colour->b);
}

void mint_TextureSetAlpha(MintTexture* self, char alpha)
{
	if (self->_alpha == NULL) SDL_SetTextureBlendMode(self->texture, SDL_BLENDMODE_BLEND);

	self->_alpha = alpha;
	SDL_SetTextureAlphaMod(self->texture, self->_alpha);
}

void mint_TextureSetupAnim(MintTexture* self, int totalAnims)
{
	self->_totalAnims = 0;
	self->anims = (MintAnim*)malloc(sizeof(MintAnim) * totalAnims);
}