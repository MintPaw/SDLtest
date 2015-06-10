#ifndef PHYS_H
#define PHYS_H

struct MintFloatPoint;
struct MintPhys;

#include <SDL.h>
#include "../display/texture.h"

struct MintDoublePoint {
	double x;
	double y;
};

struct MintPhys {
	MintTexture* mintTexture;
	MintDoublePoint velocity;
	MintDoublePoint accel;
	MintDoublePoint drag;
	MintDoublePoint maxVelocity;
};

void mint_PhysUpdate(MintPhys* phys, double elapsed);
double mint_PhysComputeVelocity(double velocity, double accel, double drag, double max, double elapsed);

#endif