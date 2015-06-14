#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "mintSDL/display/tilemap.h"
#include "mintSDL/display/texture.h"

MintTilemap* mint_TilemapCreate(SDL_Renderer* renderer, char* graphicsPath, int tileWidth, int tileHeight)
{
	MintTilemap* tilemap = (MintTilemap*)malloc(sizeof(MintTilemap));

	tilemap->map = mint_TextureFromPNG(renderer, graphicsPath);
	tilemap->tileWidth = tileWidth;
	tilemap->tileHeight = tileHeight;

	return tilemap;
}

void mint_TilemapGenerateFromCSV(MintTilemap* tilemap, char* dataPath)
{
	SDL_Texture* source = tilemap->map->texture;

	int colsInMap = mint_TransGetWidth(tilemap->map->trans) / tilemap->tileWidth;
	int rowsInMap = mint_TransGetHeight(tilemap->map->trans) / tilemap->tileHeight;

	FILE* data = fopen(dataPath, "r");
	if (data == NULL)
	{
		printf("Error loading the file.");
		return;
	}
	//NOTE (luke): maybe there is a better way to read rows and cells from a CSV
	char buffer[1024];

	while (fgets(buffer, sizeof(buffer), data) != NULL)
	{
		buffer[strlen(buffer) - 1] = '\0';

		printf("Line: %s\n", buffer);
	}

	fclose(data);
}

void mint_TilemapFree(MintTilemap* map)
{
	mint_TextureFree(map->map);
	free(map);
	map = NULL;
}