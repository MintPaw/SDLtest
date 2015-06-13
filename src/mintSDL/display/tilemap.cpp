#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "tilemap.h"
#include "texture.h"
#include "mintSDL/util/io.h"

MintTilemap* mint_TilemapCreate(SDL_Renderer* renderer, char* fileName, int tileWidth, int tileHeight)
{
	MintTilemap* tilemap = (MintTilemap*)malloc(sizeof(MintTilemap));

	tilemap->map = mint_TextureFromPNG(renderer, fileName);
	tilemap->tileWidth = tileWidth;
	tilemap->tileHeight = tileHeight;

	return tilemap;
}

void mint_TilemapCreateFromCSV(SDL_Renderer* renderer, char* path, MintTilemap* tilemap)
{
	int colsInMap = mint_TransGetWidth(tilemap->map->trans) / tilemap->tileWidth;
	int rowsInMap = mint_TransGetHeight(tilemap->map->trans) / tilemap->tileHeight;

	char* data = mint_ReadAllText(path);

	if (data != 0)
	{
		
	}

	free(data);
}