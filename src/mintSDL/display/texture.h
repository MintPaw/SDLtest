#ifndef TEXTURE_H
#define TEXTURE_H

struct MintTexture;

#include <SDL_ttf.h>
#include "mintSDL/display/anim.h"
#include "mintSDL/display/rend.h"
#include "mintSDL/display/trans.h"
#include "mintSDL/maths/phys.h"

struct MintTexture {
	SDL_Texture* texture;
	MintAnimMan* animMan;
	MintTrans* trans;
	MintRend* rend;
	MintPhys* phys;
};

MintTexture* mint_TextureFromPNG(SDL_Renderer* renderer, char* path);
MintTexture* mint_TextureFromText(SDL_Renderer* renderer, TTF_Font* font, char* text, SDL_Color colour);
MintTexture* mint_TextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);

void mint_TextureRender(MintTexture* mintTexture);
void mint_TextureFree(MintTexture* mintTexture);

#endif