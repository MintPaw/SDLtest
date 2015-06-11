#ifndef GEOM_H
#define GEOM_H

struct MintDoublePoint;

struct MintDoublePoint {
	double x;
	double y;
};

char mint_GeomPointInRect(SDL_Point* point, SDL_Rect* rect);

#endif