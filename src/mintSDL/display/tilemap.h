#ifndef TILEMAP_H
#define TILEMAP_H

struct MintTilemap;

#include <SDL.h>
#include "mintSDL/display/texture.h"

struct MintTilemap {
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect tileRects[256];

	int tileWidth;
	int tileHeight;

	char layers[8][128][128];
};

MintTilemap* mint_TilemapCreate(SDL_Renderer* renderer, char* fileName, int tileWidth, int tileHeight);
void mint_TilemapGenerateFromTiled(MintTilemap* tilemap, char* dataPath);
void mint_TilemapFree(MintTilemap* map);
void mint_TilemapRenderLayer(MintTilemap* tilemap, char layer);
char** strspl(char* str, char* del);

#endif