#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "mintSDL/system.h"
#include "mintSDL/display/anim.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/maths/phys.h"

MintTexture* mint_TextureFromNothing(MintSystem* sys)
{
	MintTexture* mintTexture = (MintTexture*)malloc(sizeof(MintTexture));

	mintTexture->texture = NULL;
	mintTexture->sys = sys;
	mintTexture->phys = NULL;
	mintTexture->animMan = mint_AnimManSetup(mintTexture);

	mintTexture->width = 0;
	mintTexture->height = 0;
	mintTexture->centre.x = mintTexture->width / 2;
	mintTexture->centre.y = mintTexture->height / 2;
	mintTexture->angle = 0;
	mintTexture->flip = SDL_FLIP_NONE;
	mintTexture->x = 0;
	mintTexture->y = 0;
	mintTexture->alpha = NULL;

	return mintTexture;
}

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

MintTexture* mint_TextureFromSurface(MintSystem* sys, SDL_Surface* surface)
{
	MintTexture* mintTexture = mint_TextureFromNothing(sys);

	mintTexture->texture = SDL_CreateTextureFromSurface(sys->sdlRenderer, surface);
	if (mintTexture->texture == NULL) {
		printf("Failed to create texture from, SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}

	mintTexture->width = surface->w;
	mintTexture->height = surface->h;

	mintTexture->animMan = mint_AnimManSetup(mintTexture);

	return mintTexture;
}

void mint_TextureLoadText(MintTexture* mintTexture, TTF_Font* font, char* text, SDL_Color colour)
{
	if (mintTexture) SDL_DestroyTexture(mintTexture->texture);

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, colour);

	if (surface == NULL) {
		printf("Failed to create surface from TTF, SDL_Error: %s\n", SDL_GetError());
		return;
	}

	mintTexture->texture = SDL_CreateTextureFromSurface(mintTexture->sys->sdlRenderer, surface);

	if (mintTexture->texture == NULL) {
		printf("Failed to create texture from, SDL_Error: %s\n", SDL_GetError());
		return;
	}

	SDL_FreeSurface(surface);
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
		quad = { mintTexture->x, mintTexture->y, mintTexture->animMan->clipRect->w, mintTexture->animMan->clipRect->h };

		SDL_RenderCopyEx(mintTexture->sys->sdlRenderer,
		                 mintTexture->texture,
		                 mintTexture->animMan->clipRect,
		                 &quad,
		                 mintTexture->angle,
		                 &mintTexture->centre,
		                 mintTexture->flip);
	} else {
		quad = { mintTexture->x, mintTexture->y, mintTexture->width, mintTexture->height };
		SDL_RenderCopyEx(mintTexture->sys->sdlRenderer,
		                 mintTexture->texture,
		                 NULL,
		                 &quad,
		                 mintTexture->angle,
		                 &mintTexture->centre,
		                 mintTexture->flip);
	}
}

void mint_TextureFree(MintTexture* mintTexture)
{
	SDL_DestroyTexture(mintTexture->texture);
	mint_PhysFree(mintTexture->phys);
	mint_AnimManFree(mintTexture->animMan);
	
	free(mintTexture);
	mintTexture = NULL;
}

void mint_TextureSetX(MintTexture* mintTexture, int value)
{
	mintTexture->x = value;

	if (mintTexture->phys) {
		b2Body* body = mintTexture->phys->body;
		body->SetTransform(b2Vec2(mint_PhysPixelToMetre((float)value), body->GetPosition().y), body->GetAngle());
	}
}

void mint_TextureSetY(MintTexture* mintTexture, int value)
{
	mintTexture->y = value;

	if (mintTexture->phys) {
		b2Body* body = mintTexture->phys->body;
		body->SetTransform(b2Vec2(body->GetPosition().x, mint_PhysPixelToMetre((float)value)), body->GetAngle());
	}
}

void mint_TextureResizeHit(MintTexture* mintTexture, int width, int height)
{
	mintTexture->width = width;
	mintTexture->height = height;

	if (mintTexture->phys) {
		mint_PhysGenerateFixture(mintTexture->phys);
	}
}

void mint_TextureSetColour(MintTexture* mintTexture, SDL_Color* colour)
{
	SDL_SetTextureColorMod(mintTexture->texture, colour->r, colour->g, colour->b);
}

void mint_TextureSetAlpha(MintTexture* mintTexture, char alpha)
{
	if (mintTexture->alpha == NULL) SDL_SetTextureBlendMode(mintTexture->texture, SDL_BLENDMODE_BLEND);

	mintTexture->alpha = alpha;
	SDL_SetTextureAlphaMod(mintTexture->texture, mintTexture->alpha);
}
