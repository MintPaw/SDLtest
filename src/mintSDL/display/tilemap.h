#ifndef TILEMAP_H
#define TILEMAP_H

struct MintTilemap;

#include <SDL.h>
#include "mintSDL/display/texture.h"

struct MintTilemap {
	MintTexture* map;
	int tileWidth;
	int tileHeight;
};

MintTilemap* mint_TilemapCreate(SDL_Renderer* renderer, char* fileName, int tileWidth, int tileHeight);
void mint_TilemapCreateFromCSV(SDL_Renderer* renderer, SDL_Surface* destSurface, char* path, MintTilemap* map);
void mint_TilemapFree(MintTilemap* map);
char** strspl(char* str, char* del);

#endif