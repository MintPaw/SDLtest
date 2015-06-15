#ifndef TILEMAP_H
#define TILEMAP_H

#define TILES_WIDE 30
#define TILES_HIGH 16
#define TOTAL_LAYERS 5
#define TOTAL_TILES 260

struct MintTilemap;

#include <SDL.h>
#include "mintSDL/display/texture.h"

struct MintTilemap {
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect tileRects[TOTAL_TILES];

	int tileWidth;
	int tileHeight;
	int indexShift;

	char layers[TOTAL_LAYERS][TILES_HIGH][TILES_WIDE];
};

MintTilemap* mint_TilemapCreate(MintSystem* sys, char* graphicsPath, int tileWidth, int tileHeight, int indexShift);
void mint_TilemapGenerateFromTiled(MintTilemap* tilemap, char* dataPath);
void mint_TilemapFree(MintTilemap* map);
void mint_TilemapRenderLayer(MintTilemap* tilemap, char layer);

#endif