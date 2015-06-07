#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "anim.h"
#include "display.h"
#include "texture.h"
#include "trans.h"

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
	if (mintTexture->texture == NULL) {
		printf("Failed to create texture from %s, SDL_Error: %s\n", path, SDL_GetError());
	}

	mintTexture->renderer = renderer;
	mintTexture->_alpha = NULL;

	mintTexture->trans = (MintTrans*)malloc(sizeof(MintTrans));
	mintTexture->trans->x = 0;
	mintTexture->trans->y = 0;
	mintTexture->trans->_width = surface->w;
	mintTexture->trans->_height = surface->h;
	
	mintTexture->trans->centre = (SDL_Point*)malloc(sizeof(SDL_Point));
	mintTexture->trans->centre->x = mintTexture->trans->_width / 2;
	mintTexture->trans->centre->y = mintTexture->trans->_height / 2;
	mintTexture->trans->angle = 0;
	mintTexture->trans->flip = SDL_FLIP_NONE;

	mintTexture->_clipRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	mintTexture->_clipRect->x = 0;
	mintTexture->_clipRect->y = 0;
	mintTexture->_clipRect->w = surface->w;
	mintTexture->_clipRect->h = surface->h;

	mintTexture->currentAnim = NULL;

	SDL_FreeSurface(surface);

	return mintTexture;
}

void mint_TextureRender(MintTexture* self)
{
	SDL_Rect quad = { self->trans->x, self->trans->y, self->_clipRect->w, self->_clipRect->h };
	SDL_RenderCopyEx(self->renderer, self->texture, self->_clipRect, &quad, self->trans->angle, self->trans->centre, self->trans->flip);
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

void mint_TextureSetupAnims(MintTexture* self, int totalAnims)
{
	self->anims = (MintAnim*)malloc(sizeof(MintAnim) * totalAnims);

	int i;
	for (i = 0; i < totalAnims; i++) {
		self->anims[i].texture = self;
	}
}

void mint_TexturePlayAnimByIndex(MintTexture* self, int index)
{
	self->currentAnim = &self->anims[index];
}