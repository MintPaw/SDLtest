#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "mintSDL/display/tilemap.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/util/array.h"

MintTilemap* mint_TilemapCreate(SDL_Renderer* renderer, char* graphicsPath, int tileWidth, int tileHeight)
{
	MintTilemap* tilemap = (MintTilemap*)malloc(sizeof(MintTilemap));

	tilemap->map = mint_TextureFromPNG(renderer, graphicsPath);
	tilemap->tileWidth = tileWidth;
	tilemap->tileHeight = tileHeight;

	return tilemap;
}

void mint_TilemapGenerateFromTiled(MintTilemap* tilemap, char* dataPath)
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
	// NOTE(jeru): Note these limitations
	char layerStrings[8][128][128] = { -99 };
	char layerNumber = 0;
	char rowNumber = 0;
	char colNumber = 0;
	char adding = 0;
	char* token;

	while (fgets(buffer, sizeof(buffer), data) != NULL)
	{
		buffer[strlen(buffer) - 1] = '\0';

		if (!adding && strstr(buffer, "<data encoding=\"csv\">") != NULL) {
			rowNumber = 0;
			adding = 1;
			continue;
		}
		
		if (adding && strstr(buffer, "</data>") != NULL) {
			adding = 0;
			layerNumber++;
			continue;
		}

		if (adding) {
			colNumber = 0;
			token = strtok(buffer, ",");

			while (token != NULL) {
				layerStrings[layerNumber][rowNumber][colNumber] = atoi(token);
				token = strtok(NULL, ",");
				colNumber++;
			}
			// printf("Would add %s to [%d, %d, X]\n", buffer, layerNumber, rowNumber);

			rowNumber++;
		}
	}

	mint_ArrayPrint(layerStrings[0][0], 20);

	fclose(data);
}

void mint_TilemapFree(MintTilemap* map)
{
	mint_TextureFree(map->map);
	free(map);
	map = NULL;
}