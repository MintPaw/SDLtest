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

	mintTexture->sys = sys;
	mintTexture->texture = NULL;

	mintTexture->x = 0;
	mintTexture->y = 0;
	mintTexture->width = 0;
	mintTexture->height = 0;
	mintTexture->alpha = NULL;
	mintTexture->angle = 0;
	mintTexture->centre = { mintTexture->width / 2,  mintTexture->height / 2 }; 
	mintTexture->flip = SDL_FLIP_NONE;
	mintTexture->renderRect = { 0, 0, 0, 0 };

	mintTexture->body = NULL;
	mintTexture->dynamic = 0;
	mintTexture->hitboxOffset = { 0, 0 };

	mintTexture->currentAnim = NULL;
	mintTexture->anims = NULL;
	mintTexture->clipRect = NULL;
	mintTexture->totalAnims = 0;

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
	
	mintTexture->width = surface->w;
	mintTexture->height = surface->h;

	mintTexture->texture = SDL_CreateTextureFromSurface(mintTexture->sys->sdlRenderer, surface);

	if (mintTexture->texture == NULL) {
		printf("Failed to create texture from, SDL_Error: %s\n", SDL_GetError());
		return;
	}

	SDL_FreeSurface(surface);
}

void mint_TextureUpdate(MintTexture* mintTexture, float elapsed)
{
	mint_AnimUpdate(mintTexture, elapsed);
	mint_PhysUpdate(mintTexture, elapsed);
}

void mint_TextureRender(MintTexture* mintTexture)
{
	if (mintTexture->clipRect) {
		mintTexture->renderRect = { mintTexture->x, mintTexture->y, mintTexture->clipRect->w, mintTexture->clipRect->h };
	} else {
		mintTexture->renderRect = { mintTexture->x, mintTexture->y, mintTexture->width, mintTexture->height };
	}

	SDL_RenderCopyEx(mintTexture->sys->sdlRenderer,
	                 mintTexture->texture,
	                 mintTexture->clipRect,
	                 &mintTexture->renderRect,
	                 mintTexture->angle,
	                 &mintTexture->centre,
	                 mintTexture->flip);
}

void mint_TextureFree(MintTexture* mintTexture)
{
	SDL_DestroyTexture(mintTexture->texture);
	mint_AnimFree(mintTexture);
	
	free(mintTexture);
	mintTexture = NULL;
}

void mint_TextureSetX(MintTexture* mintTexture, int value)
{
	mintTexture->x = value;

	if (mintTexture->body) {
		b2Body* body = mintTexture->body;
		body->SetTransform(b2Vec2(mint_PhysPixelToMetre((float)value + mintTexture->width / 2), body->GetPosition().y), body->GetAngle());
	}
}

void mint_TextureSetY(MintTexture* mintTexture, int value)
{
	mintTexture->y = value;

	if (mintTexture->body) {
		b2Body* body = mintTexture->body;
		body->SetTransform(b2Vec2(body->GetPosition().x, mint_PhysPixelToMetre((float)value + mintTexture->height / 2)), body->GetAngle());
	}
}

void mint_TextureResizeHit(MintTexture* mintTexture, int width, int height)
{
	mintTexture->width = width;
	mintTexture->height = height;

	if (mintTexture) {
		mint_PhysGenerateFixture(mintTexture);
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
