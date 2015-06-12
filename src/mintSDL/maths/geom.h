#ifndef GEOM_H
#define GEOM_H

struct MintDoublePoint;
struct MintCircle;

struct MintDoublePoint {
	double x;
	double y;
};

struct MintCircle {
	int x;
	int y;
	int r;
};

int mint_GeomPointDisance(SDL_Point* a, SDL_Point* b);
char mint_GeomPointInRect(SDL_Point* point, SDL_Rect* rect);
char mint_GeomRectInRect(SDL_Rect* a, SDL_Rect* b);
char mint_GeomCircleinCircle(MintCircle* a, MintCircle* b);
double mint_GeomDotProduct(MintDoublePoint* a, MintDoublePoint* b);
void mint_GeomNormalizeDoublePoint(MintDoublePoint* point);

#endif