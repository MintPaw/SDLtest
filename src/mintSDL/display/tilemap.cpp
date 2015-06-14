#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

	char* data = mint_ReadAllText(path);
	//NOTE (luke): maybe there is a better way to read rows and cells from a CSV
	char *tokenLine, *toFree, *string, *tokenChar;

	if (data != 0)
	{
		toFree = string = strdup(data);

		while ((tokenLine = strsep(&string, "\n")) != NULL)
		{
			while ((tokenChar = strsep(&tokenLine, ",")) != NULL)
			{
				for (int col = 0; col < colsInMap; col++)
				{
					for (int row = 0; row < rowsInMap; row++)
					{
						int index = col + row;
						if (index == (int)tokenChar)
						{

						}
					}
					continue;
				}
			}
		}
	}

	free(data);
}