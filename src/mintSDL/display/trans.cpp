#include <stdlib.h>
#include "mintSDL/display/texture.h"

MintTrans* mint_TransSetup(int width, int height)
{
	MintTrans* trans = (MintTrans*)malloc(sizeof(MintTrans));

	trans->x = 0;
	trans->y = 0;
	trans->_width = width;
	trans->_height = height;
	trans->centre.x = width / 2;
	trans->centre.y = height / 2;
	trans->angle = 0;
	trans->flip = SDL_FLIP_NONE;

	return trans;
}

int mint_TransGetWidth(MintTrans* trans)
{
	return trans->_width;
}

int mint_TransGetHeight(MintTrans* trans)
{
	return trans->_height;
}

void mint_TransFree(MintTrans* trans)
{
	free(trans);
	trans = NULL;
}