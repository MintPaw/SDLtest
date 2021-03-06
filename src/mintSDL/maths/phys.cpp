#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <Box2D/Box2D.h>
#include "mintSDL/display/texture.h"
#include "mintSDL/maths/phys.h"
#include "mintSDL/maths/maths.h"

b2World* mint_PhysSetupWorld(float gravityX, float gravityY)
{
	b2World* world = new b2World({ gravityX, gravityY });

	return world;
}

void mint_PhysEnable(MintTexture* mintTexture, char dynamic, float density)
{
	mintTexture->body = NULL;
	mintTexture->dynamic = dynamic;
	// phys->density = density;

	mint_PhysGenerateFixture(mintTexture);
}

void mint_PhysGenerateFixture(MintTexture* mintTexture)
{
	if (mintTexture->body != NULL) {
		mintTexture->sys->world->DestroyBody(mintTexture->body);
	}

	b2BodyDef groundBodyDef;
	groundBodyDef.type = mintTexture->dynamic ? b2_dynamicBody : b2_staticBody;
	groundBodyDef.fixedRotation = true;
	groundBodyDef.position.Set(mint_PhysPixelToMetre(mintTexture->x + mintTexture->width / 2), mint_PhysPixelToMetre(mintTexture->y + mintTexture->height / 2));

	b2PolygonShape shape;
	float perc = .8;
	b2Vec2* verts = (b2Vec2*)malloc(8 * sizeof(b2Vec2));
	verts[0].Set(mint_PhysPixelToMetre(-mintTexture->width / 2) * perc, mint_PhysPixelToMetre(-mintTexture->height / 2));
	verts[1].Set(mint_PhysPixelToMetre(-mintTexture->width / 2), mint_PhysPixelToMetre(mintTexture->height / 2) * perc);
	verts[2].Set(mint_PhysPixelToMetre(-mintTexture->width / 2), mint_PhysPixelToMetre(mintTexture->height / 2));
	verts[3].Set(mint_PhysPixelToMetre(mintTexture->width / 2) * perc, mint_PhysPixelToMetre(mintTexture->height / 2));
	verts[4].Set(mint_PhysPixelToMetre(mintTexture->width / 2), mint_PhysPixelToMetre(mintTexture->height / 2));
	verts[5].Set(mint_PhysPixelToMetre(mintTexture->width / 2), mint_PhysPixelToMetre(-mintTexture->height / 2) * perc);
	verts[6].Set(mint_PhysPixelToMetre(mintTexture->width / 2), mint_PhysPixelToMetre(-mintTexture->height / 2));
	verts[7].Set(mint_PhysPixelToMetre(-mintTexture->width / 2) * perc, mint_PhysPixelToMetre(-mintTexture->height / 2));
	shape.Set(verts, 8);
	// shape.SetAsBox(mint_PhysPixelToMetre((float)(mintTexture->width / 2)), mint_PhysPixelToMetre((float)(mintTexture->height / 2)));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;

	mintTexture->body = mintTexture->sys->world->CreateBody(&groundBodyDef);
	mintTexture->body->CreateFixture(&fixtureDef);
}

void mint_PhysSetGravity(MintSystem* sys, float gravityX, float gravityY) { sys->world->SetGravity({ gravityX, gravityY }); }
void mint_PhysStepWorld(MintSystem* sys, float elapsed) { sys->world->Step((float)elapsed, 6, 2); }
float mint_PhysMetreToPixel(float metre) { return (float)(metre * 100); }
float mint_PhysPixelToMetre(float pixel) { return (float)(pixel / 100); }
void mint_PhysApplyForce(MintTexture* mintTexture, float forceX, float forceY) { mintTexture->body->ApplyForce({ forceX, forceY }, mintTexture->body->GetWorldCenter(), 1); }

b2Vec2 mint_PhysGetDynamic(MintTexture* mintTexture) { return mintTexture->body->GetLinearVelocity(); }

b2Vec2 mint_PhysGetVelocity(MintTexture* mintTexture) { return mintTexture->body->GetLinearVelocity(); }
void mint_PhysSetVelocity(MintTexture* mintTexture, float veloX, float veloY) { mintTexture->body->SetLinearVelocity(b2Vec2(veloX, veloY)); }

void mint_PhysSetDamping(MintTexture* mintTexture, float damping) { mintTexture->body->SetLinearDamping(damping); }

void mint_PhysUpdate(MintTexture* mintTexture, float elapsed)
{
	if (!mintTexture->body) return;

	b2AABB aabb = mintTexture->body->GetFixtureList()[0].GetAABB(0);
	b2Vec2 pos = mintTexture->body->GetPosition();

	pos.x = mint_PhysMetreToPixel(aabb.GetCenter().x - aabb.GetExtents().x) - mintTexture->hitboxOffset.x;
	pos.y = mint_PhysMetreToPixel(aabb.GetCenter().y - aabb.GetExtents().y) - mintTexture->hitboxOffset.y;

	mintTexture->x = (int)pos.x;
	mintTexture->y = (int)pos.y;
}

void mint_PhysFreeWorld(MintSystem* sys)
{
	sys->world->~b2World();
}