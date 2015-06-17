#define _CRT_SECURE_NO_WARNINGS

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 832;

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "mintSDL/system.h"
#include "mintSDL/display/tilemap.h"
#include "mintSDL/display/draw.h"
#include "mintSDL/util/input.h"
#include "mintSDL/util/timer.h"
#include "mintSDL/maths/phys.h"

void _updateLoop(MintSystem* sys);
void _close(MintSystem* sys);

MintSystem* mint_SystemSetup(char vsync)
{
	MintSystem* sys = (MintSystem*)malloc(sizeof(MintSystem));
	sys->sdlWindow = NULL;
	sys->sdlRenderer = NULL;
	sys->input = NULL;
	sys->timer = NULL;
	sys->world = NULL;
	sys->stage = -1;
	sys->quit = 0;
	sys->debugDraw = 0;
	sys->totalTextures = 0;
	sys->totalFonts = 0;
	sys->fpsCounter = NULL;
	sys->tilemap = NULL;
	sys->gameWidth = SCREEN_WIDTH;
	sys->gameHeight = SCREEN_HEIGHT;
	
	int i;
	for (i = 0; i < MAX_TEXTURES; i++) sys->textures[i] = NULL;
	for (i = 0; i < MAX_FONTS; i++) sys->fonts[i] = NULL;

	sys->start = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to init SDL_ERROR: %s\n", SDL_GetError());
		return 0;
	} else {
		sys->sdlWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sys->gameWidth, sys->gameHeight, SDL_WINDOW_SHOWN);
		if (sys->sdlWindow == NULL) {
			printf("Failed to create window SDL_ERROR: %s\n", SDL_GetError());
			return 0;
		} else {
			// TODO(jeru): Vsync option
			if (vsync)
			{
				sys->sdlRenderer = SDL_CreateRenderer(sys->sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			} else {
				sys->sdlRenderer = SDL_CreateRenderer(sys->sdlWindow, -1, SDL_RENDERER_ACCELERATED);
			}
			if (sys->sdlRenderer == NULL) {
				printf("Failed to create renderer, SDL_Error: \n", SDL_GetError());
			}
		}
	}

	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 0;
	}

	if(TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 0;
	}

	sys->input = mint_InputSetup();
	sys->timer = mint_TimerSetup();
	sys->world = mint_PhysSetupWorld(0, 10);

	SDL_UpdateWindowSurface(sys->sdlWindow);

	return sys;
}

char mint_SystemInit(MintSystem* sys, char showFps)
{
	if (showFps) {
		sys->fpsCounter = mint_TextureFromNothing(sys);
	}

	sys->start(sys);

	return 1;
}

void mint_SystemAddFont(MintSystem* sys, char* path)
{
	sys->fonts[sys->totalFonts] = TTF_OpenFont(path, 28);
	sys->totalFonts++;
}

void mint_SystemFullScreen(MintSystem* sys, char fullscreen)
{
	SDL_SetWindowFullscreen(sys->sdlWindow, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

void mint_SystemPreUpdate(MintSystem* sys)
{
	if (sys->stage == DRAW) mint_SystemPostDraw(sys);
	if (sys->stage != -1 && sys->stage != POST_DRAW) printf("Warning: forcing bad call of preupdate");
	sys->stage = PRE_UPDATE;

	{ // Handle Events
		while (SDL_PollEvent(&sys->event) != 0) {

			if (sys->event.type == SDL_KEYDOWN ||
			    sys->event.type == SDL_KEYUP ||
	        sys->event.type == SDL_MOUSEMOTION ||
			    sys->event.type == SDL_MOUSEBUTTONDOWN ||
			    sys->event.type == SDL_MOUSEBUTTONUP) mint_InputUpdate(sys->input, &sys->event);

			if (sys->event.type == SDL_QUIT || mint_InputCheckKey(sys->input, SDL_SCANCODE_ESCAPE)) sys->quit = 1;
		}
	}
}

void mint_SystemUpdate(MintSystem* sys)
{
	if (sys->stage == DRAW) mint_SystemPostDraw(sys);
	if (sys->stage == -1 || sys->stage == POST_DRAW) mint_SystemPreUpdate(sys);
	if (sys->stage != PRE_UPDATE) printf("Warning: forcing bad call of update");
	sys->stage = UPDATE;

	mint_TimerUpdate(sys->timer, (float)(SDL_GetTicks() / 1000.0));

	mint_PhysStepWorld(sys->world, sys->timer->elapsed);

	int i;
	for (i = 0; i < sys->totalTextures; i++) {
		if (sys->textures[i] == NULL) continue;
		mint_TextureUpdate(sys->textures[i], sys->timer->elapsed);
	}

	if (sys->fpsCounter) {
		char fpsText[16];
		_itoa((int)sys->timer->fpsAverage, fpsText, 10);
		strcat(fpsText, " avg fps");
		mint_TextureLoadText(sys->fpsCounter, sys->fonts[0], fpsText, { 0, 0, 0, 0 } );
	}
}

void mint_SystemPostUpdate(MintSystem* sys)
{
	if (sys->stage != UPDATE) printf("Warning: forcing bad call of postupdate");
	sys->stage = POST_UPDATE;
}

void mint_SystemPreDraw(MintSystem* sys)
{
	if (sys->stage == UPDATE) mint_SystemPostUpdate(sys);
	if (sys->stage != POST_UPDATE) printf("Warning: forcing bad call of predraw");
	sys->stage = PRE_DRAW;

	SDL_SetRenderDrawColor(sys->sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(sys->sdlRenderer);
}

void mint_SystemDraw(MintSystem* sys)
{
	if (sys->stage == UPDATE) mint_SystemPostUpdate(sys);
	if (sys->stage == POST_UPDATE) mint_SystemPreDraw(sys);
	if (sys->stage != PRE_DRAW) printf("Warning: forcing bad call of draw");
	sys->stage = DRAW;

	if (sys->fpsCounter) mint_TextureRender(sys->fpsCounter);

	int i;
	for (i = 0; i < sys->totalTextures; i++) {
		if (sys->textures[i] == NULL) continue;
		mint_TextureRender(sys->textures[i]);
	}

	if (sys->tilemap != NULL) {
		mint_TilemapRenderLayer(sys->tilemap, 0);
		// mint_TilemapRenderLayer(sys->tilemap, 1);
		// mint_TilemapRenderLayer(sys->tilemap, 2);
		// mint_TilemapRenderLayer(sys->tilemap, 3);
		// mint_TilemapRenderLayer(sys->tilemap, 4);
	}

	if (sys->debugDraw) {
		SDL_Color green = { 0, 255, 0, 255 };
		b2Body* bodyList = sys->world->world->GetBodyList();

		for(;;)
		{
			if (bodyList == NULL) break;
			b2AABB aabb = bodyList->GetFixtureList()[0].GetAABB(0);
			
			mint_DrawRect(sys, mint_PhysMetreToPixel(aabb.GetCenter().x),
			                   mint_PhysMetreToPixel(aabb.GetCenter().y),
			                   mint_PhysMetreToPixel(aabb.GetExtents().x * 2),
			                   mint_PhysMetreToPixel(aabb.GetExtents().y * 2),
			                   &green);

			bodyList = bodyList->GetNext();
		}
	}
}

void mint_SystemPostDraw(MintSystem* sys)
{
	if (sys->stage != DRAW) printf("Warning: forcing bad call of postupdate");
	sys->stage = POST_DRAW;

	SDL_RenderPresent(sys->sdlRenderer);

	if (sys->quit) _close(sys);

	// vsync
	// if ((1.0 / 60.0 * 1000.0) - (SDL_GetTicks() - timer->ticks) > 0) SDL_Delay((int)((1.0 / 60.0 * 1000.0) - (SDL_GetTicks() - timer->ticks)));
}

void mint_SystemAddTexture(MintSystem* sys, MintTexture* mintTexture)
{
	sys->textures[sys->totalTextures] = mintTexture;
	sys->totalTextures++;

	// if (i == MAX_TEXTURES - 1) mint_SystemCompactTextures(sys);
}

void mint_SystemRemoveTexture(MintSystem* sys, MintTexture* mintTexture, char free)
{
	int i;
	for (i = 0; i < MAX_TEXTURES; i++) if (sys->textures[i] == mintTexture) break;

	if (i < MAX_TEXTURES - 1) sys->textures[i] = NULL;

	if (free) mint_TextureFree(mintTexture);
}

void mint_SystemRemoveAll(MintSystem* sys)
{
	int i;
	for (i = 0; i < sys->totalTextures; i++) {
		if (sys->textures[i] == NULL) continue;
		mint_TextureFree(sys->textures[i]);
	}
}

void _close(MintSystem* sys)
{
	mint_SystemRemoveAll(sys);

	SDL_DestroyWindow(sys->sdlWindow);
	SDL_DestroyRenderer(sys->sdlRenderer);
	sys->sdlWindow = NULL;

	mint_InputFree(sys->input);
	mint_TimerFree(sys->timer);
	mint_PhysFreeWorld(sys->world);
	if (sys->tilemap != NULL) mint_TilemapFree(sys->tilemap);

	int i;
	for (i = 0; i < sys->totalFonts; i++) {
		if (sys->fonts[i] == NULL) continue;
		TTF_CloseFont(sys->fonts[i]);
	}

	free(sys);

	SDL_Quit();

#ifdef _CRTDBG_MAP_ALLOC
	_CrtDumpMemoryLeaks();
#endif
	exit(0);
}