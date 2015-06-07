#ifndef TEXTURE_H
#define TEXTURE_H

struct MintTexture;

#include "anim.h"

struct MintTexture {
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	MintAnim* anims;
	MintAnim* currentAnim;
	int x;
	int y;
	double angle;
	SDL_Point* centre;
	SDL_RendererFlip flip;
	int _width;
	int _height;
	int _alpha;
	SDL_Rect* _clipRect;
};

char mint_TextureSetup();
MintTexture* mint_TextureFromPNG(SDL_Renderer* renderer, char* path);

int mint_TextureGetWidth(MintTexture* self);
int mint_TextureGetHeight(MintTexture* self);
void mint_TextureRender(MintTexture* self);
void mint_TextureSetColour(MintTexture* self, SDL_Color* colour);
void mint_TextureSetAlpha(MintTexture* self, char alpha);
void mint_TextureSetupAnims(MintTexture* self, int totalAnims);
void mint_TexturePlayAnimByIndex(MintTexture* self, int index);

#endif