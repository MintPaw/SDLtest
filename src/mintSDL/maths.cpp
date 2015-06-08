#include <SDL.h>

char mint_MathsPointInRect(SDL_Point* point, SDL_Rect* rect)
{
	// Corners in ax,ay,bx,by,dx,dy
	// Point in x, y

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

	if ((point->x - ax) * bax + (point->y - ay) * bay < 0) return false;
	if ((point->x - bx) * bax + (point->y - by) * bay > 0) return false;
	if ((point->x - ax) * dax + (point->y - ay) * day < 0) return false;
	if ((point->x - dx) * dax + (point->y - dy) * day > 0) return false;

	return true;
}