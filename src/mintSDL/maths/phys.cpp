#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <Box2d/Box2d.h>
#include "mintSDL/display/texture.h"
#include "mintSDL/maths/phys.h"
#include "mintSDL/maths/maths.h"

MintPhysWorld* mint_PhysSetupWorld(float gravityX, float gravityY)
{
	MintPhysWorld* world = (MintPhysWorld*)malloc(sizeof(MintPhysWorld));
	world->world = new b2World({gravityX, gravityY});

	return world;
}

MintPhys* mint_PhysCreate(MintTexture* mintTexture, MintPhysWorld* physWorld, char dynamic, float density)
{
	MintPhys* phys = (MintPhys*)malloc(sizeof(MintPhys));
	phys->mintTexture = mintTexture;

	b2BodyDef groundBodyDef;
	groundBodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
	groundBodyDef.position.Set(mint_PhysPixelToMetre(mintTexture->trans->x), mint_PhysPixelToMetre(mintTexture->trans->y));

	b2PolygonShape shape;
	shape.SetAsBox(mint_PhysPixelToMetre(mintTexture->trans->_width / 2), mint_PhysPixelToMetre(mintTexture->trans->_height / 2));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = density;
	fixtureDef.friction = 0.3f;

	phys->world = physWorld;
	phys->shape = shape;
	phys->body = physWorld->world->CreateBody(&groundBodyDef);
	phys->body->CreateFixture(&fixtureDef);

	return phys;
}

void mint_PhysStepWorld(MintPhysWorld* world, double elapsed)
{
	world->world->Step((float)elapsed, 6, 2);
}

float mint_PhysPixelToMetre(double pixel)
{
	return (float)(pixel / 100);
}

void mint_PhysUpdate(MintPhys* phys, double elapsed)
{
	b2Vec2 pos = phys->body->GetPosition();
	phys->mintTexture->trans->x = pos.x;
	phys->mintTexture->trans->y = pos.y;
}

void mint_PhysFree(MintPhys* phys)
{
	free(phys);
	phys = NULL;
}