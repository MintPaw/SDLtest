#ifndef TEXTURE_H
#define TEXTURE_H

struct MintTexture;

#include <SDL_ttf.h>
#include "mintSDL/system.h"
#include "mintSDL/display/anim.h"
#include "mintSDL/display/rend.h"
#include "mintSDL/display/trans.h"
#include "mintSDL/maths/phys.h"

struct MintTexture {
	MintSystem* sys;
	SDL_Texture* texture;
	MintAnimMan* animMan;
	MintTrans* trans;
	MintPhys* phys;
};

MintTexture* mint_TextureFromPNG(MintSystem* sys, char* path);
MintTexture* mint_TextureFromText(MintSystem* sys, TTF_Font* font, char* text, SDL_Color colour);
MintTexture* mint_TextureFromSurface(MintSystem* sys, SDL_Surface* surface);

void mint_TextureUpdate(MintTexture* mintTexture, float elapsed);
void mint_TextureRender(MintTexture* mintTexture);
void mint_TextureFree(MintTexture* mintTexture);

#endif