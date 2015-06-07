#ifndef TEXTURE_H
#define TEXTURE_H

#include "anim.h"

struct MintTexture {
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	MintAnim* anims;
	int x;
	int y;
	int _width;
	int _height;
	int _alpha;
	int _totalAnims;
};

char mint_TextureSetup();
MintTexture* mint_TextureFromPNG(SDL_Renderer* renderer, char* path);

int mint_TextureGetWidth(MintTexture* self);
int mint_TextureGetHeight(MintTexture* self);
void mint_TextureRender(MintTexture* self);
void mint_TextureSetColour(MintTexture* self, SDL_Color* colour);
void mint_TextureSetAlpha(MintTexture* self, char alpha);
void mint_TextureSetupAnim(MintTexture* self, int totalAnims);

#endif