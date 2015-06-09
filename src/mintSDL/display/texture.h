#ifndef TEXTURE_H
#define TEXTURE_H

struct MintTexture;

#include <SDL_ttf.h>
#include "anim.h"
#include "display.h"
#include "trans.h"

struct MintTexture {
	SDL_Texture* texture;
	MintAnimMan* animMan;
	MintTrans* trans;
	MintRend* rend;
};

MintTexture* mint_TextureFromPNG(SDL_Renderer* renderer, char* path);
MintTexture* mint_TextureFromText(SDL_Renderer* renderer, TTF_Font* font, char* text, SDL_Color colour);
MintTexture* mint_TextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);

void mint_TextureRender(MintTexture* mintTexture);
void mint_TextureSetupAnimMan(MintTexture* mintTexture, int totalAnims);
void mint_TextureFree(MintTexture* mintTexture);

#endif