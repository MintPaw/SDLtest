#ifndef TILEMAP_H
#define TILEMAP_H

struct MintTilemap;

#include <SDL.h>
#include "texture.h"

struct MintTilemap {
	MintTexture* map;
	int offsetX;
	int offsetY;
}

MintTilemap* mint_TilemapCreate(MintTexture* spritesheet, int offsetX, int offsetY);
MintTexture* mint_TilemapGetTexture(int col, int row);
MintTexture* mint_TilemapDrawFromJSON(char* fileName, MintTilemap* map);
void mint_TilemapFree(MintTilemap* map);

#endif
