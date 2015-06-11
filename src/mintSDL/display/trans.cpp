#include <stdlib.h>
#include "mintSDL/display/texture.h"

MintTrans* mint_TransSetup(MintTexture* mintTexture, int width, int height)
{
	MintTrans* trans = (MintTrans*)malloc(sizeof(MintTrans));

	trans->mintTexture = mintTexture;
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

void mint_TransSetX(MintTrans* trans, int value)
{
	trans->x = value;
	trans->mintTexture->phys->_rect.x = value;
}

void mint_TransSetY(MintTrans* trans, int value)
{
	trans->y = value;
	trans->mintTexture->phys->_rect.y = value;
}

int mint_TransGetX(MintTrans* trans)
{
	return trans->x;
}

int mint_TransGetY(MintTrans* trans)
{
	return trans->y;
}

void mint_TransFree(MintTrans* trans)
{
	free(trans);
	trans = NULL;
}