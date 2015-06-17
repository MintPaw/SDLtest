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
	world->world = new b2World({ gravityX, gravityY });

	return world;
}

void mint_PhysEnable(MintTexture* mintTexture, MintPhysWorld* physWorld, char dynamic, float density)
{
	MintPhys* phys = (MintPhys*)malloc(sizeof(MintPhys));
	phys->mintTexture = mintTexture;
	mintTexture->phys = phys;

	b2BodyDef groundBodyDef;
	groundBodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
	groundBodyDef.fixedRotation = true;
	groundBodyDef.position.Set(mint_PhysPixelToMetre((float)mintTexture->x), mint_PhysPixelToMetre((float)mintTexture->y));

	b2PolygonShape shape;
	shape.SetAsBox(mint_PhysPixelToMetre((float)(mintTexture->width / 2)), mint_PhysPixelToMetre((float)(mintTexture->height / 2)));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = density;
	fixtureDef.friction = 0.3f;

	phys->world = physWorld;
	phys->shape = shape;
	phys->body = physWorld->world->CreateBody(&groundBodyDef);
	phys->body->CreateFixture(&fixtureDef);
}

void mint_PhysSetGravity(MintPhysWorld* world, float gravityX, float gravityY) { world->world->SetGravity({ gravityX, gravityY }); }
void mint_PhysStepWorld(MintPhysWorld* world, float elapsed) { world->world->Step((float)elapsed, 6, 2); }
float mint_PhysMetreToPixel(float metre) { return (float)(metre * 100); }
float mint_PhysPixelToMetre(float pixel) { return (float)(pixel / 100); }
void mint_PhysApplyForce(MintPhys* phys, float forceX, float forceY) { phys->body->ApplyForce({ forceX, forceY }, phys->body->GetWorldCenter(), 1); }
void mint_PhysSetVelocity(MintPhys* phys, float veloX, float veloY) { phys->body->SetLinearVelocity(b2Vec2(veloX, veloY)); }
b2Vec2 mint_PhysGetVelocity(MintPhys* phys) { return phys->body->GetLinearVelocity(); }
void mint_PhysSetDamping(MintPhys* phys, float damping) { phys->body->SetLinearDamping(damping); }

void mint_PhysUpdate(MintPhys* phys, float elapsed)
{
	if (!phys) return;

	b2Vec2 pos = phys->body->GetPosition();
	pos.x = mint_PhysMetreToPixel(pos.x);
	pos.y = mint_PhysMetreToPixel(pos.y);

	phys->mintTexture->x = (int)pos.x;
	phys->mintTexture->y = (int)pos.y;
}

void mint_PhysFree(MintPhys* phys)
{
	free(phys);
	phys = NULL;
}

void mint_PhysFreeWorld(MintPhysWorld* world)
{
	world->world->~b2World();
	free(world->world);
	free(world);
}