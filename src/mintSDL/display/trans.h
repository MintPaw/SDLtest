#ifndef TRANS_H
#define TRANS_H

struct MintTrans;

#include <SDL.h>
#include "mintSDL/display/texture.h"

struct MintTrans {
	MintTexture* mintTexture;

	float angle;
	SDL_Point centre;
	SDL_RendererFlip flip;
	int _width;
	int _height;
	int _x;
	int _y;
};

MintTrans* mint_TransSetup(MintTexture* mintTexture, int width, int height);
void mint_TransSetX(MintTrans* trans, int value);
void mint_TransSetY(MintTrans* trans, int value);
int mint_TransGetWidth(MintTrans* trans);
int mint_TransGetHeight(MintTrans* trans);
void mint_TransFree(MintTrans* trans);

#endif