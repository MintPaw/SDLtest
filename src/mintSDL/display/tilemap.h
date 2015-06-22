#ifndef TILEMAP_H
#define TILEMAP_H

#define TILES_WIDE 30
#define TILES_HIGH 16
#define TOTAL_LAYERS 5
#define TOTAL_TILES 260
#define TOTAL_BODIES 1024

#define GRAPHICAL_BOT 0
#define PHYSICAL_1 1
#define PHYSICAL_2 2
#define GRAPHICAL_TOP 3
#define HELPER 4

struct MintTilemap;

#include <SDL.h>
#include <Box2D/Box2D.h>
#include "mintSDL/display/texture.h"

struct MintTilemap {
	MintSystem* sys;
	SDL_Texture* texture;
	SDL_Rect tileRects[TOTAL_TILES];
	b2Body* bodies[TOTAL_BODIES];

	int tileWidth;
	int tileHeight;
	int indexShift;

	char layers[TOTAL_LAYERS][TILES_HIGH][TILES_WIDE];
};

void mint_TilemapCreate(MintSystem* sys, char* graphicsPath, int tileWidth, int tileHeight, int indexShift);
void mint_TilemapGenerateFromTiled(MintTilemap* tilemap, char* dataPath);
void mint_TilemapFree(MintTilemap* map);
void mint_TilemapRenderLayer(MintTilemap* tilemap, char layer);

#endif