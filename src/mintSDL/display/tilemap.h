#ifndef TILEMAP_H
#define TILEMAP_H

struct MintTilemap;

#include <SDL.h>
#include "mintSDL/display/texture.h"

struct MintTilemap {
	MintTexture* map;
	int tileWidth;
	int tileHeight;

	char graphicalTopLayerData[128][128];
	char physicalLayerData[128][128];
	char graphicalBotLayerData[128][128];
};

MintTilemap* mint_TilemapCreate(SDL_Renderer* renderer, char* fileName, int tileWidth, int tileHeight);
void mint_TilemapGenerateFromTiled(MintTilemap* tilemap, char* dataPath);
void mint_TilemapFree(MintTilemap* map);
char** strspl(char* str, char* del);

#endif