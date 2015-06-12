#include <stdlib.h>
#include <Box2D/Box2d.h>
#include "mintSDL/display/texture.h"

MintTrans* mint_TransSetup(MintTexture* mintTexture, int width, int height)
{
	MintTrans* trans = (MintTrans*)malloc(sizeof(MintTrans));

	trans->mintTexture = mintTexture;
	trans->_width = width;
	trans->_height = height;
	trans->centre.x = width / 2;
	trans->centre.y = height / 2;
	trans->angle = 0;
	trans->flip = SDL_FLIP_NONE;
	trans->_x = 0;
	trans->_y = 0;

	return trans;
}

void mint_TransSetX(MintTrans* trans, int value)
{
	trans->_x = value;

	if (trans->mintTexture->phys) {
		b2Body* body = trans->mintTexture->phys->body;
		body->SetTransform(b2Vec2((float)value, body->GetPosition().y), body->GetAngle());
	}
}

void mint_TransSetY(MintTrans* trans, int value)
{
	trans->_y = value;

	if (trans->mintTexture->phys) {
		b2Body* body = trans->mintTexture->phys->body;
		body->SetTransform(b2Vec2(body->GetPosition().y, (float)value), body->GetAngle());
	}
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