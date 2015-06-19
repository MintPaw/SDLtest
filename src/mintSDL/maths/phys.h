#ifndef PHYS_H
#define PHYS_H

struct MintFloatPoint;

#include <SDL.h>
#include <Box2D/Box2d.h>
#include "mintSDL/display/texture.h"
#include "mintSDL/maths/geom.h"

b2World* mint_PhysSetupWorld(float gravityX, float gravityY);
void mint_PhysEnable(MintTexture* mintTexture, char dynamic, float density);
void mint_PhysGenerateFixture(MintTexture* mintTexture);
float mint_PhysMetreToPixel(float metre);
float mint_PhysPixelToMetre(float pixel);
void mint_PhysSetGravity(MintSystem* sys, float gravityX, float gravityY);
void mint_PhysApplyForce(MintTexture* mintTexture, float forceX, float forceY);
void mint_PhysSetVelocity(MintTexture* mintTexture, float veloX, float veloY);
void mint_PhysSetDamping(MintTexture* mintTexture, float damping);
b2Vec2 mint_PhysGetVelocity(MintTexture* mintTexture);

void mint_PhysStepWorld(MintSystem* sys, float elapsed);
void mint_PhysUpdate(MintTexture* mintTexture, float elapsed);
void mint_PhysFreeWorld(MintSystem* sys);

#endif