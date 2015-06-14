#define _CRT_SECURE_NO_WARNINGS
#define TILES_WIDE 30
#define TILES_HIGH 16

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
	
	SDL_Surface* surface = IMG_Load(graphicsPath);

	if (surface == NULL) {
		printf("Failed to create surface from %s, SDL_Error: %s\n", graphicsPath, SDL_GetError());
		return NULL;
	}

	tilemap->texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (tilemap->texture == NULL) {
		printf("Failed to create texture from, SDL_Error: %s\n", SDL_GetError());
	}

	SDL_FreeSurface(surface);

	tilemap->tileWidth = tileWidth;
	tilemap->tileHeight = tileHeight;

	return tilemap;
}

void mint_TilemapGenerateFromTiled(MintTilemap* tilemap, char* dataPath)
{
	FILE* data = fopen(dataPath, "r");
	if (data == NULL)
	{
		printf("Error loading the file.");
		return;
	}
	//NOTE (luke): maybe there is a better way to read rows and cells from a CSV
	char buffer[1024];
	// NOTE(jeru): Note these limitations
	char layerStrings[8][TILES_HIGH][TILES_WIDE] = { -99 };
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

			rowNumber++;
		}
	}

	int i;
	for (i = 0; i < TILES_HIGH; i++) mint_ArrayPrint(layerStrings[0][i], TILES_WIDE);

	fclose(data);
}

void mint_TilemapFree(MintTilemap* map)
{
	SDL_DestroyTexture(map->texture);
	free(map);
	map = NULL;
}