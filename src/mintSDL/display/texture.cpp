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

	mintTexture->rend = (MintRend*)malloc(sizeof(MintRend));

	mintTexture->rend->texture = mintTexture;
	mintTexture->rend->renderer = renderer;
	mintTexture->rend->_alpha = NULL;
	mintTexture->rend->_clipRect = NULL;

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


	SDL_FreeSurface(surface);

	return mintTexture;
}

void mint_TextureRender(MintTexture* self)
{
	if (self->rend->_clipRect) {
		// printf("Rendering anim\n");
		SDL_Rect quad = { self->trans->x, self->trans->y, self->rend->_clipRect->w, self->rend->_clipRect->h };
		SDL_RenderCopyEx(self->rend->renderer, self->texture, self->rend->_clipRect, &quad, self->trans->angle, self->trans->centre, self->trans->flip);
	} else {
		SDL_Rect quad = { self->trans->x, self->trans->y, self->trans->_width, self->trans->_height };
		SDL_RenderCopyEx(self->rend->renderer, self->texture, NULL, &quad, self->trans->angle, self->trans->centre, self->trans->flip);
	}
}

void mint_TextureSetupAnimMan(MintTexture* self, int totalAnims)
{
	self->animMan = (MintAnimMan*)malloc(sizeof(MintAnimMan));
	self->animMan->anims = (MintAnim*)malloc(sizeof(MintAnim) * totalAnims);

	self->animMan->currentAnim = NULL;
	self->animMan->texture = self;

	int i;
	for (i = 0; i < totalAnims; i++) {
		self->animMan->anims[i].man = self->animMan;
	}
}