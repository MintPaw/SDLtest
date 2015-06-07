#ifndef TRANS_H
#define TRANS_H

#include <SDL.h>

struct MintTrans {
	int x;
	int y;
	double angle;
	SDL_Point* centre;
	SDL_RendererFlip flip;
	int _width;
	int _height;
};

int mint_TransGetWidth(MintTrans* trans);
int mint_TransGetHeight(MintTrans* trans);

#endif