#include <stdlib.h>
#include "mintSDL/display/texture.h"
#include "mintSDL/maths/phys.h"

MintPhys* mint_PhysCreate(MintTexture* mintTexture)
{
	MintPhys* phys = (MintPhys*)malloc(sizeof(MintPhys));

	phys->mintTexture = mintTexture;
	phys->velocity = { 0, 0 };
	phys->accel = { 0, 0 };
	phys->drag = { 0, 0 };
	phys->maxVelocity = { 0, 0 };

	return phys;
}

void mint_PhysUpdate(MintPhys* phys, double elapsed)
{
	double velocityDelta;
	double delta;

	// This would be for angular velo
	// velocityDelta = 0.5 * mint_PhysComputeVelocity(phys->angularVelocity, phys->angualAccel, phys->angularDrag, phys->maxAngular, elapsed) - phys->angularVelocity;
	// phys->angularVelocity += velocityDelta;
	// phys->mintTexture->trans->angle += phys->angularVelocity * elapsed;
	// phys->angularVelocity += velocityDelta;

	velocityDelta = 0.5 * (mint_PhysComputeVelocity(phys->velocity.x, phys->accel.x, phys->drag.x, phys->maxVelocity.x, elapsed) - phys->velocity.x);
	phys->velocity.x += velocityDelta;
	delta = phys->velocity.x * elapsed;
	phys->velocity.x += velocityDelta;
	phys->mintTexture->trans->x += delta;

	velocityDelta = 0.5 * (mint_PhysComputeVelocity(phys->velocity.y, phys->accel.y, phys->drag.y, phys->maxVelocity.y, elapsed) - phys->velocity.y);
	phys->velocity.y += velocityDelta;
	delta = phys->velocity.y * elapsed;
	phys->velocity.y += velocityDelta;
	phys->mintTexture->trans->y += delta;
}

double mint_PhysComputeVelocity(double velocity, double accel, double drag, double max, double elapsed)
{
	double drag2;

	if (accel) {
		velocity += accel * elapsed;
	} else if (drag) {
		drag2 = drag * elapsed;
		if (velocity - drag2 > 0) {
			velocity -= drag2;
		} else if (velocity + drag2 < 0) {
			velocity += drag2;
		} else {
			velocity = 0;
		}
	}

	if (velocity && max) {
		// NOTE(jeru): Add clamp?
		if (velocity > max) velocity = max;
		if (velocity < -max) velocity = -max;
	}

	return velocity;
}

void mint_PhysFree(MintPhys* phys)
{
	free(phys);
	phys = NULL;
}