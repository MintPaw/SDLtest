#ifndef TEXTURE_H
#define TEXTURE_H

struct MintTexture;

#include <SDL_ttf.h>
#include "mintSDL/system.h"
#include "mintSDL/display/anim.h"
#include "mintSDL/maths/phys.h"

struct MintTexture {
	MintSystem* sys;
	SDL_Texture* texture;
	MintAnimMan* animMan;
	MintPhys* phys;

	float angle;
	SDL_Point centre;
	SDL_RendererFlip flip;
	int width;
	int height;
	int x;
	int y;
	unsigned char alpha;
};

MintTexture* mint_TextureFromNothing(MintSystem* sys);
MintTexture* mint_TextureFromPNG(MintSystem* sys, char* path);
MintTexture* mint_TextureFromSurface(MintSystem* sys, SDL_Surface* surface);

void mint_TextureLoadText(MintTexture* mintTexture, TTF_Font* font, char* text, SDL_Color colour);
void mint_TextureUpdate(MintTexture* mintTexture, float elapsed);
void mint_TextureRender(MintTexture* mintTexture);
void mint_TextureFree(MintTexture* mintTexture);

void mint_TextureSetX(MintTexture* mintTexture, int value);
void mint_TextureSetY(MintTexture* mintTexture, int value);
void mint_TextureSetColour(MintTexture* mintTexture, SDL_Color* colour);
void mint_TextureSetAlpha(MintTexture* mintTexture, char alpha);
void mint_TextureResizeHit(MintTexture* mintTexture, int width, int height);

#endif