#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "mintSDL/display/tilemap.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/util/array.h"

MintTilemap* mint_TilemapCreate(SDL_Renderer* renderer, char* graphicsPath, int tileWidth, int tileHeight, int indexShift)
{
	MintTilemap* tilemap = (MintTilemap*)malloc(sizeof(MintTilemap));
	tilemap->renderer = renderer;
	tilemap->tileWidth = tileWidth;
	tilemap->tileHeight = tileHeight;
	tilemap->indexShift = indexShift - 1;
	
	SDL_Surface* surface = IMG_Load(graphicsPath);

	if (surface == NULL) {
		printf("Failed to create surface from %s, SDL_Error: %s\n", graphicsPath, SDL_GetError());
		return NULL;
	}

	tilemap->texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (tilemap->texture == NULL) {
		printf("Failed to create texture from, SDL_Error: %s\n", SDL_GetError());
	}

	int i;
	int j;
	int currentRect = 0;
	for (i = 0; i < surface->h / tileHeight; i++) {
		for (j = 0; j < surface->w / tileWidth; j++) {
			tilemap->tileRects[currentRect] = { j * tileWidth, i * tileHeight, tileWidth, tileHeight };
			currentRect++;
		}
	}

	SDL_FreeSurface(surface);

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
	memset(tilemap->layers, -1, sizeof(tilemap->layers));
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
				tilemap->layers[layerNumber][rowNumber][colNumber] = atoi(token);
				token = strtok(NULL, ",");
				colNumber++;
			}

			rowNumber++;
		}
	}

	fclose(data);
}

void mint_TilemapRenderLayer(MintTilemap* tilemap, char layer)
{
	int i;
	int j;
	SDL_Rect quad;
	SDL_Rect clip;

	for (i = 0; i < TILES_HIGH; i++) {
		for (j = 0; j < TILES_WIDE; j++) {
			if (tilemap->layers[layer][i][j] <= 0) continue;

			quad = { j * tilemap->tileWidth, i * tilemap->tileHeight, tilemap->tileWidth, tilemap->tileHeight };
			clip = tilemap->tileRects[tilemap->layers[layer][i][j] + tilemap->indexShift];

			SDL_RenderCopy(tilemap->renderer, tilemap->texture, &clip, &quad);
		}
	}
}

void mint_TilemapFree(MintTilemap* map)
{
	SDL_DestroyTexture(map->texture);
	free(map);
	map = NULL;
}