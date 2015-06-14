#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "mintSDL/maths/geom.h"
#include "mintSDL/maths/maths.h"

int mint_GeomPointDisance(SDL_Point* a, SDL_Point* b)
{
	return (int)sqrt((a->x - b->x)^2 + (a->y - b->y)^2);
}

char mint_GeomPointInRect(SDL_Point* point, SDL_Rect* rect)
{
	int ax = rect->x;
	int ay = rect->y;
	int bx = rect->x + rect->w;
	int by = rect->y;
	int dx = rect->x;
	int dy = rect->y + rect->h;

	int bax = bx - ax;
	int bay = by - ay;
	int dax = dx - ax;
	int day = dy - ay;

	if ((point->x - ax) * bax + (point->y - ay) * bay < 0) return 0;
	if ((point->x - bx) * bax + (point->y - by) * bay > 0) return 0;
	if ((point->x - ax) * dax + (point->y - ay) * day < 0) return 0;
	if ((point->x - dx) * dax + (point->y - dy) * day > 0) return 0;

	return 1;
}

char mint_GeomRectInRect(SDL_Rect* a, SDL_Rect* b)
{
	if(a->x + a->w < b->x || a->x > b->x + b->w) return 0;
	if(a->y + a->h < b->y || a->y > b->y + b->h) return 0;

	return 1;
}

char mint_GeomCircleinCircle(MintCircle* a, MintCircle* b)
{
	float r = (float)(a->r + b->r);
	r *= r;
	return r < ((a->x + b->x)^2) + ((a->y + b->y)^2);
}

float mint_GeomDotProduct(MintFloatPoint* a, MintFloatPoint* b)
{
	return a->x * b->x + a->y * b->y;
}

void mint_GeomNormalizeFloatPoint(MintFloatPoint* point, float multiply)
{
	float highest = (float)mint_MathMax(abs((int)point->x), abs((int)point->y));
	point->x /= highest;
	point->y /= highest;

	point->x *= multiply;
	point->y *= multiply;
}