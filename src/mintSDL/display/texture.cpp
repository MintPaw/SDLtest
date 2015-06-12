#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "mintSDL/display/anim.h"
#include "mintSDL/display/rend.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/display/trans.h"
#include "mintSDL/maths/phys.h"

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

	mintTexture->rend = mint_RendSetup(mintTexture, renderer);
	mintTexture->trans = mint_TransSetup(mintTexture, surface->w, surface->h);
	mintTexture->phys = NULL;

	mintTexture->animMan = mint_AnimManSetup(mintTexture);

	return mintTexture;
}

void mint_TextureUpdate(MintTexture* mintTexture, double elapsed)
{
	mint_PhysUpdate(mintTexture->phys, elapsed);
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

void mint_TextureFree(MintTexture* mintTexture)
{
	SDL_DestroyTexture(mintTexture->texture);
	mint_RendFree(mintTexture->rend);
	mint_TransFree(mintTexture->trans);
	mint_PhysFree(mintTexture->phys);
	mint_AnimManFree(mintTexture->animMan);
	
	free(mintTexture);
	mintTexture = NULL;
}