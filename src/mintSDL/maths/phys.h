#ifndef PHYS_H
#define PHYS_H

struct MintFloatPoint;
struct MintPhysWorld;
struct MintPhys;

#include <SDL.h>
#include <Box2D/Box2d.h>
#include "mintSDL/display/texture.h"
#include "mintSDL/maths/geom.h"

struct MintPhys {
	MintTexture* mintTexture;
	b2Body* body;
	char isDynamic;
	float density;

	SDL_Rect rect;
};

b2World* mint_PhysSetupWorld(float gravityX, float gravityY);
void mint_PhysEnable(MintTexture* mintTexture, char dynamic, float density);
void mint_PhysGenerateFixture(MintPhys* phys);
float mint_PhysMetreToPixel(float metre);
float mint_PhysPixelToMetre(float pixel);
void mint_PhysSetGravity(MintSystem* sys, float gravityX, float gravityY);
void mint_PhysApplyForce(MintPhys* phys, float forceX, float forceY);
void mint_PhysSetVelocity(MintPhys* phys, float veloX, float veloY);
void mint_PhysSetDamping(MintPhys* phys, float damping);
b2Vec2 mint_PhysGetVelocity(MintPhys* phys);

void mint_PhysStepWorld(MintSystem* sys, float elapsed);
void mint_PhysUpdate(MintPhys* phys, float elapsed);
void mint_PhysFree(MintPhys* phys);
void mint_PhysFreeWorld(MintSystem* sys);

#endif