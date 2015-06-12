#ifndef PHYS_H
#define PHYS_H

struct MintFloatPoint;
struct MintPhysWorld;
struct MintPhys;

#include <SDL.h>
#include <Box2D/Box2d.h>
#include "mintSDL/display/texture.h"
#include "mintSDL/maths/geom.h"

struct MintPhysWorld {
	b2World* world;
};

struct MintPhys {
	MintTexture* mintTexture;
	MintPhysWorld* world;
	b2PolygonShape shape;
	b2Body* body;

	SDL_Rect rect;
};

MintPhysWorld* mint_PhysSetupWorld(float gravityX, float gravityY);
MintPhys* mint_PhysCreate(MintTexture* mintTexture, MintPhysWorld* physWorld, char dynamic, float density);
float mint_PhysMetreToPixel(double metre);
float mint_PhysPixelToMetre(double pixel);
void mint_PhysSetGravity(MintPhysWorld* world, float gravityX, float gravityY);
void mint_PhysApplyForce(MintPhys* phys, float forceX, float forceY);
void mint_PhysSetVelocity(MintPhys* phys, float veloX, float veloY);

void mint_PhysStepWorld(MintPhysWorld* world, double elapsed);
void mint_PhysUpdate(MintPhys* phys, double elapsed);
void mint_PhysFree(MintPhys* phys);

#endif