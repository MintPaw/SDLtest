#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void mint_TilemapCreateFromCSV(SDL_Renderer* renderer, SDL_Surface* destSurface, char* path, MintTilemap* tilemap)
{
	SDL_Texture* source = tilemap->map->texture;

	int colsInMap = mint_TransGetWidth(tilemap->map->trans) / tilemap->tileWidth;
	int rowsInMap = mint_TransGetHeight(tilemap->map->trans) / tilemap->tileHeight;

	FILE* data = fopen(path, "r");
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