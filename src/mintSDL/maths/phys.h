#ifndef PHYS_H
#define PHYS_H

struct MintFloatPoint;
struct MintPhysWorld;
struct MintPhys;

#include <SDL.h>
#include <Box2d/Dynamics/b2World.h>
#include "mintSDL/display/texture.h"
#include "mintSDL/maths/geom.h"

struct MintPhysWorld {
	b2World world;
};

struct MintPhys {
	MintTexture* mintTexture;
	double restitution;
	double mass;

	MintDoublePoint velocity;
	MintDoublePoint accel;
	MintDoublePoint drag;
	MintDoublePoint maxVelocity;

	SDL_Rect rect;
};

MintPhysWorld* mint_PhysSetupWorld(float gravityX, float gravityY);
MintPhys* mint_PhysCreate(MintTexture* mintTexture);
void mint_PhysUpdate(MintPhys* phys, double elapsed);
double mint_PhysComputeVelocity(double velocity, double accel, double drag, double max, double elapsed);
void mint_PhysCollideRectRect(MintPhys* a, MintPhys* b);
void mint_PhysResolveRectCollision(MintPhys* a, MintPhys* b, MintDoublePoint* normal);
void mint_PhysFree(MintPhys* phys);

#endif