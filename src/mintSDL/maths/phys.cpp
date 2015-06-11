#include <math.h>
#include <stdlib.h>
#include <stdio.h>
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
	phys->restitution = 0;
	phys->mass = 1;

	return phys;
}

void mint_PhysUpdate(MintPhys* phys, double elapsed)
{
	phys->rect.x = phys->mintTexture->trans->x;
	phys->rect.y = phys->mintTexture->trans->y;
	phys->rect.w = phys->mintTexture->trans->_width;
	phys->rect.h = phys->mintTexture->trans->_height;

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

void mint_PhysCollideRectRect(MintPhys* a, MintPhys* b)
{
	if (mint_GeomRectInRect(&a->rect, &b->rect))
	{
		MintDoublePoint normal = { 0, 0 };
		double xIn = 999;
		double yIn = 999;

		if (a->rect.x < b->rect.x) {
			xIn = a->rect.x + a->rect.w - b->rect.x;
		} else {
			xIn = b->rect.x + b->rect.w - a->rect.x;
			xIn = -xIn;
		}

		if (a->rect.y < b->rect.y) {
			yIn = a->rect.y + a->rect.h - b->rect.y;
		} else {
			yIn = b->rect.y + b->rect.h - a->rect.y;
			yIn = -yIn;
		}

		if (abs((int)xIn) < abs((int)yIn)) {
			if (xIn == 0) return;
			if (xIn > 0) normal = { 1, 0 };
			if (xIn < 0) normal = { -1, 0 };
		} else if (abs((int)xIn) > abs((int)yIn)) {
			if (yIn == 0) return;
			if (yIn > 0) normal = { 0, 1 };
			if (yIn < 0) normal = { 0, -1 };
		}

		mint_PhysResolveRectCollision(a, b, &normal);
	}
}

void mint_PhysResolveRectCollision(MintPhys* a, MintPhys* b, MintDoublePoint* normal)
{
	// Calculate relative velocity
	MintDoublePoint rv;
	rv.x = b->velocity.x - a->velocity.x;
	rv.y = b->velocity.y - a->velocity.y;

	// Calculate relative velocity in terms of the normal direction
	double velAlongNormal = mint_GeomDotProduct(&rv, normal);

	// Do not resolve if velocities are separating
	if(velAlongNormal > 0) return;

	// Calculate restitution
	// TODO(jeru): Add min/max
	double e = a->restitution < b->restitution ? a->restitution : a->restitution;

	// Calculate impulse scalar
	double j = -(1 + e) * velAlongNormal;
	j /= 1 / a->mass + 1 / b->mass;

	// Apply impulse
	MintDoublePoint impulse;
	impulse.x = j * normal->x;
	impulse.y = j * normal->y;

	a->velocity.x -= 1 / a->mass * impulse.x;
	a->velocity.y -= 1 / a->mass * impulse.y;

	b->velocity.x += 1 / b->mass * impulse.x;
	b->velocity.y += 1 / b->mass * impulse.y;
}

void mint_PhysFree(MintPhys* phys)
{
	free(phys);
	phys = NULL;
}