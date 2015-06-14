#ifndef GEOM_H
#define GEOM_H

#define GEOM_LEFT 0
#define GEOM_RIGHT 1
#define GEOM_UP 2
#define GEOM_DOWN 3

struct MintFloatPoint;
struct MintCircle;

struct MintFloatPoint {
	float x;
	float y;
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
float mint_GeomDotProduct(MintFloatPoint* a, MintFloatPoint* b);
void mint_GeomNormalizeFloatPoint(MintFloatPoint* point, float multiply);

#endif