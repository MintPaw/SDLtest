#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "mintSDL/system.h"
#include "mintSDL/display/anim.h"
#include "mintSDL/display/rend.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/display/trans.h"
#include "mintSDL/maths/phys.h"

MintTexture* mint_TextureFromPNG(MintSystem* sys, char* path)
{
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL) {
		printf("Failed to create surface from %s, SDL_Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	MintTexture* mintTexture = mint_TextureFromSurface(sys, surface);

	SDL_FreeSurface(surface);

	return mintTexture;
}

MintTexture* mint_TextureFromText(MintSystem* sys, TTF_Font* font, char* text, SDL_Color colour)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, colour);

	if (surface == NULL) {
		printf("Failed to create surface from TTF, SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}

	MintTexture* mintTexture = mint_TextureFromSurface(sys, surface);

	SDL_FreeSurface(surface);

	return mintTexture;
}

MintTexture* mint_TextureFromSurface(MintSystem* sys, SDL_Surface* surface)
{
	MintTexture* mintTexture = (MintTexture*)malloc(sizeof(MintTexture));

	mintTexture->texture = SDL_CreateTextureFromSurface(sys->sdlRenderer, surface);
	if (mintTexture->texture == NULL) {
		printf("Failed to create texture from, SDL_Error: %s\n", SDL_GetError());
	}

	mintTexture->sys = sys;
	mintTexture->trans = mint_TransSetup(mintTexture, surface->w, surface->h);
	mintTexture->phys = NULL;

	mintTexture->animMan = mint_AnimManSetup(mintTexture);

	return mintTexture;
}

void mint_TextureUpdate(MintTexture* mintTexture, float elapsed)
{
	mint_AnimUpdate(mintTexture->animMan, elapsed);
	mint_PhysUpdate(mintTexture->phys, elapsed);
}

void mint_TextureRender(MintTexture* mintTexture)
{
	SDL_Rect quad;
	if (mintTexture->animMan->clipRect) {
		quad = { mintTexture->trans->_x, mintTexture->trans->_y, mintTexture->animMan->clipRect->w, mintTexture->animMan->clipRect->h };

		SDL_RenderCopyEx(mintTexture->sys->sdlRenderer,
		                 mintTexture->texture,
		                 mintTexture->animMan->clipRect,
		                 &quad,
		                 mintTexture->trans->angle,
		                 &mintTexture->trans->centre,
		                 mintTexture->trans->flip);
	} else {
		quad = { mintTexture->trans->_x, mintTexture->trans->_y, mintTexture->trans->_width, mintTexture->trans->_height };
		SDL_RenderCopyEx(mintTexture->sys->sdlRenderer,
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
	mint_TransFree(mintTexture->trans);
	mint_PhysFree(mintTexture->phys);
	mint_AnimManFree(mintTexture->animMan);
	
	free(mintTexture);
	mintTexture = NULL;
}