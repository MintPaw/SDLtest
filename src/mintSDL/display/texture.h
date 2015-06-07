#ifndef TEXTURE_H
#define TEXTURE_H

struct MintTexture;

#include "trans.h"
#include "anim.h"

struct MintTexture {
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	MintAnimMan* animMan;
	MintTrans* trans;
	int _alpha;
	SDL_Rect* _clipRect;
};

char mint_TextureSetup();
MintTexture* mint_TextureFromPNG(SDL_Renderer* renderer, char* path);

void mint_TextureRender(MintTexture* self);
void mint_TextureSetColour(MintTexture* self, SDL_Color* colour);
void mint_TextureSetAlpha(MintTexture* self, char alpha);
void mint_TextureSetupAnims(MintTexture* self, int totalAnims);
void mint_TexturePlayAnimByIndex(MintTexture* self, int index);
void mint_AnimSetupMan(MintTexture* self, int totalAnims);

#endif