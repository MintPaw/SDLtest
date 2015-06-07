#ifndef TEXTURE_H
#define TEXTURE_H

struct MintTexture;

#include "anim.h"
#include "display.h"
#include "trans.h"

struct MintTexture {
	SDL_Texture* texture;
	MintAnimMan* animMan;
	MintTrans* trans;
	MintRend* rend;
};

char mint_TextureSetup();
MintTexture* mint_TextureFromPNG(SDL_Renderer* renderer, char* path);

void mint_TextureRender(MintTexture* mintTexture);
void mint_TextureSetupAnimMan(MintTexture* mintTexture, int totalAnims);

#endif