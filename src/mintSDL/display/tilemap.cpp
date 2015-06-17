#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <Box2d/Box2D.h>
#include "mintSDL/display/tilemap.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/util/array.h"

void mint_TilemapCreate(MintSystem* sys, char* graphicsPath, int tileWidth, int tileHeight, int indexShift)
{
	sys->tilemap = (MintTilemap*)malloc(sizeof(MintTilemap));
	sys->tilemap->sys = sys;
	sys->tilemap->tileWidth = tileWidth;
	sys->tilemap->tileHeight = tileHeight;
	sys->tilemap->indexShift = indexShift - 1;
	
	SDL_Surface* surface = IMG_Load(graphicsPath);

	if (surface == NULL) {
		printf("Failed to create surface from %s, SDL_Error: %s\n", graphicsPath, SDL_GetError());
		return;
	}

	sys->tilemap->texture = SDL_CreateTextureFromSurface(sys->sdlRenderer, surface);
	if (sys->tilemap->texture == NULL) {
		printf("Failed to create texture from, SDL_Error: %s\n", SDL_GetError());
	}

	int i;
	int j;
	int currentRect = 0;
	for (i = 0; i < surface->h / tileHeight; i++) {
		for (j = 0; j < surface->w / tileWidth; j++) {
			sys->tilemap->tileRects[currentRect] = { j * tileWidth, i * tileHeight, tileWidth, tileHeight };
			currentRect++;
		}
	}

	SDL_FreeSurface(surface);
}

void mint_TilemapGenerateFromTiled(MintTilemap* tilemap, char* dataPath)
{
	FILE* data = fopen(dataPath, "r");
	if (data == NULL)
	{
		printf("Error loading the file.");
		return;
	}

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

	int i;
	int j;
	int currentBody = 0;
	for (i = 0; i < TILES_HIGH; i++) {
		for (j = 0; j < TILES_WIDE; j++) {

			b2BodyDef groundBodyDef;
			groundBodyDef.type = b2_staticBody;
			groundBodyDef.fixedRotation = true;
			groundBodyDef.position.Set(mint_PhysPixelToMetre(tilemap->tileWidth * j - tilemap->tileWidth / 2),
			                           mint_PhysPixelToMetre(tilemap->tileWidth * i - tilemap->tileWidth / 2));


			b2FixtureDef fixtureDef;
			fixtureDef.density = 0;
			fixtureDef.friction = 0;

			b2PolygonShape shape;
			fixtureDef.shape = &shape;
			shape.SetAsBox(mint_PhysPixelToMetre((float)(tilemap->tileWidth / 2)), mint_PhysPixelToMetre((float)(tilemap->tileHeight / 2)));

			tilemap->bodies[currentBody] = tilemap->sys->world->world->CreateBody(&groundBodyDef);
			tilemap->bodies[currentBody]->CreateFixture(&fixtureDef);
			currentBody++;
		}
	}
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

			SDL_RenderCopy(tilemap->sys->sdlRenderer, tilemap->texture, &clip, &quad);
		}
	}
}

void mint_TilemapFree(MintTilemap* map)
{
	SDL_DestroyTexture(map->texture);
	free(map);
	map = NULL;
}