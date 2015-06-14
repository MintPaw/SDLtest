#ifndef DRAW_G
#define DRAW_G

#include "mintSDL/system.h"

void mint_DrawRect(MintSystem* sys, int x, int y, int width, int height, SDL_Color* colour);
void mint_DrawLine(MintSystem* sys, int x1, int y1, int x2, int y2, SDL_Color* colour);

#endif