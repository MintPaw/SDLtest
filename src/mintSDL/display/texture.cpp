#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "anim.h"
#include "rend.h"
#include "texture.h"
#include "trans.h"
#include "../maths/phys.h"

MintTexture* mint_TextureFromPNG(SDL_Renderer* renderer, char* path)
{
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL) {
		printf("Failed to create surface from %s, SDL_Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	MintTexture* mintTexture = mint_TextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	return mintTexture;
}

MintTexture* mint_TextureFromText(SDL_Renderer* renderer, TTF_Font* font, char* text, SDL_Color colour)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, colour);

	if (surface == NULL) {
		printf("Failed to create surface from TTF, SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}

	MintTexture* mintTexture = mint_TextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	return mintTexture;
}

MintTexture* mint_TextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface)
{
	MintTexture* mintTexture = (MintTexture*)malloc(sizeof(MintTexture));

	mintTexture->texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (mintTexture->texture == NULL) {
		printf("Failed to create texture from, SDL_Error: %s\n", SDL_GetError());
	}

	mintTexture->rend = (MintRend*)malloc(sizeof(MintRend));

	mintTexture->rend->mintTexture = mintTexture;
	mintTexture->rend->renderer = renderer;
	mintTexture->rend->_alpha = NULL;
	mintTexture->rend->_clipRect = NULL;

	mintTexture->trans = (MintTrans*)malloc(sizeof(MintTrans));
	mintTexture->trans->x = 0;
	mintTexture->trans->y = 0;
	mintTexture->trans->_width = surface->w;
	mintTexture->trans->_height = surface->h;
	mintTexture->trans->centre.x = mintTexture->trans->_width / 2;
	mintTexture->trans->centre.y = mintTexture->trans->_height / 2;
	mintTexture->trans->angle = 0;
	mintTexture->trans->flip = SDL_FLIP_NONE;

	mintTexture->animMan = NULL;

	mintTexture->phys = (MintPhys*)malloc(sizeof(MintPhys));
	mintTexture->phys->mintTexture = mintTexture;
	mintTexture->phys->velocity = { 0, 0 };
	mintTexture->phys->accel = { 0, 0 };
	mintTexture->phys->drag = { 0, 0 };
	mintTexture->phys->maxVelocity = { 0, 0 };

	return mintTexture;
}

void mint_TextureRender(MintTexture* mintTexture)
{
	if (mintTexture->rend->_clipRect) {
		SDL_Rect quad = { mintTexture->trans->x,
		                  mintTexture->trans->y,
		                  mintTexture->rend->_clipRect->w,
		                  mintTexture->rend->_clipRect->h };

		SDL_RenderCopyEx(mintTexture->rend->renderer,
		                 mintTexture->texture,
		                 mintTexture->rend->_clipRect,
		                 &quad,
		                 mintTexture->trans->angle,
		                 &mintTexture->trans->centre,
		                 mintTexture->trans->flip);
	} else {
		SDL_Rect quad = { mintTexture->trans->x,
		                  mintTexture->trans->y,
		                  mintTexture->trans->_width,
		                  mintTexture->trans->_height };

		SDL_RenderCopyEx(mintTexture->rend->renderer,
		                 mintTexture->texture,
		                 NULL,
		                 &quad,
		                 mintTexture->trans->angle,
		                 &mintTexture->trans->centre,
		                 mintTexture->trans->flip);
	}
}

void mint_TextureSetupAnimMan(MintTexture* mintTexture, int totalAnims)
{
	mintTexture->animMan = (MintAnimMan*)malloc(sizeof(MintAnimMan));
	mintTexture->animMan->anims = (MintAnim*)malloc(sizeof(MintAnim) * totalAnims);
	mintTexture->animMan->totalAnims = totalAnims;

	mintTexture->animMan->currentAnim = NULL;
	mintTexture->animMan->mintTexture = mintTexture;

	int i;
	for (i = 0; i < totalAnims; i++) {
		mintTexture->animMan->anims[i].man = mintTexture->animMan;
	}
}

void mint_TextureFree(MintTexture* mintTexture)
{
	SDL_DestroyTexture(mintTexture->texture);
	free(mintTexture->trans);
	free(mintTexture->rend);

	if (mintTexture->animMan) mint_AnimManFree(mintTexture->animMan);

	free(mintTexture);
	mintTexture = NULL;
}