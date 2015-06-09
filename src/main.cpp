#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "mintSDL\input.h"
#include "mintSDL\timer.h"
#include "mintSDL\display\display.h"
#include "mintSDL\display\anim.h"
#include "mintSDL\display\geom.h"
#include "mintSDL\display\texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void close();
void gameLoop();
void geomExampleLoop();
void mintTextureExampleLoop();
void mintSetColourInputExampleLoop();
void mintSetAlphaInputExampleLoop();
void mintTextureAnimExampleLoop();
void mintTextureTransformExampleLoop();
void mintTextureTTFExampleLoop();
void mintTextureButtonExampleLoop();
void mintTimerExampleLoop();

/*
	Todo:
		Free MintTexture
		Free MintTimer
		Cap fps if no vsync
		Impliment or remove timer pausing

	Notes:
		You can't push additional animations or frames after inits, is the a problem?
		Centre point is going to break when animations happen, also size breaks
*/

SDL_Window* sdlWindow = NULL;
SDL_Surface* sdlScreenSurface = NULL;
SDL_Renderer* sdlRenderer = NULL;
TTF_Font *ttfOpenSans = NULL;
MintInput *input;
MintTimer *timer;

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to init SDL_ERROR: %s\n", SDL_GetError());
	} else {
		sdlWindow = SDL_CreateWindow("SDL Test",
		                             SDL_WINDOWPOS_UNDEFINED,
		                             SDL_WINDOWPOS_UNDEFINED,
		                             SCREEN_WIDTH,
		                             SCREEN_HEIGHT,
		                             SDL_WINDOW_SHOWN);
		if (sdlWindow == NULL) {
			printf("Failed to create window SDL_ERROR: %s\n", SDL_GetError());
		} else {
			sdlScreenSurface = SDL_GetWindowSurface(sdlWindow);
			sdlRenderer = mint_DisplayCreateRenderer(sdlWindow, 0);
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

	ttfOpenSans = TTF_OpenFont("assets/font/OpenSansRegular.ttf", 28);

	input = mint_InputSetup();
	timer = mint_TimerSetup();

	SDL_UpdateWindowSurface(sdlWindow);

	// gameLoop();
	// geomExampleLoop();
	// mintTextureExampleLoop();
	// mintSetColourInputExampleLoop();
	// mintSetAlphaInputExampleLoop();
	// mintTextureAnimExampleLoop();
	// mintTextureTransformExampleLoop();
	// mintTextureTTFExampleLoop();
	// mintTextureButtonExampleLoop();
	mintTimerExampleLoop();

	close();

	return 0;
}

void gameLoop()
{
	SDL_Event e;
	char quit = 0;

	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);
			
			SDL_RenderPresent(sdlRenderer);
		}
	}
}

void close()
{
	SDL_DestroyWindow(sdlWindow);
	SDL_DestroyRenderer(sdlRenderer);
	sdlWindow = NULL;

	mint_InputFree(input);
	TTF_CloseFont(ttfOpenSans);

	SDL_Quit();
}

void geomExampleLoop()
{
	SDL_Event e;
	char quit = 0;

	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);
			
			mint_GeomDrawRect(sdlRenderer, 0, 0, 100, 100, 0xFF0000FF);
			mint_GeomDrawLine(sdlRenderer, 100, 100, 200, 200, 0xFF0000FF);
			mint_GeomDrawLine(sdlRenderer, 200, 200, 300, 100, 0xFF0000FF);
			mint_GeomDrawRect(sdlRenderer, 300, 50, 100, 50, 0xFF00FFFF);
			
			SDL_RenderPresent(sdlRenderer);
		}
	}
}

void mintTextureExampleLoop()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* texture = mint_TextureFromPNG(sdlRenderer, "assets/img/pngSplash.png");
	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);
			
			mint_TextureRender(texture);
			
			SDL_RenderPresent(sdlRenderer);
		}
	}
}

void mintSetColourInputExampleLoop()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* texture = mint_TextureFromPNG(sdlRenderer, "assets/img/pngSplash.png");
	SDL_Color colour = { 255, 255, 255, 0 };
	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);
			
			if (mint_InputCheckStatus(input, SDL_SCANCODE_Q)) colour.r += 10;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_A)) colour.r -= 10;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_W)) colour.g += 10;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_S)) colour.g -= 10;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_E)) colour.b += 10;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_D)) colour.b -= 10;

			mint_TextureRender(texture);
			mint_RendSetColour(texture->rend, &colour);
			
			SDL_RenderPresent(sdlRenderer);
		}
	}
}

void mintSetAlphaInputExampleLoop()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* texture = mint_TextureFromPNG(sdlRenderer, "assets/img/pngSplash.png");
	unsigned char alpha = 255;
	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);
			
			if (mint_InputCheckStatus(input, SDL_SCANCODE_Q)) alpha += 10;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_A)) alpha -= 10;

			mint_RendSetAlpha(texture->rend, alpha);
			mint_TextureRender(texture);
			
			SDL_RenderPresent(sdlRenderer);
		}
	}
}

void mintTextureAnimExampleLoop()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* texture = mint_TextureFromPNG(sdlRenderer, "assets/img/animation.png");
	mint_TextureSetupAnimMan(texture, 1);

	mint_AnimCreate(texture->animMan, 0, "anim1", 4);
	mint_AnimDefineLinearStripFrames(mint_AnimGetByIndex(texture->animMan, 0), 64, 1);
	mint_AnimPlay(mint_AnimGetByIndex(texture->animMan, 0));

	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);

			mint_TextureRender(texture);
			mint_AnimNextFrame(texture->animMan);
			
			SDL_RenderPresent(sdlRenderer);
		}
	}
}

void mintTextureTransformExampleLoop()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* arrow = mint_TextureFromPNG(sdlRenderer, "assets/img/arrow.png");

	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			if (mint_InputCheckStatus(input, SDL_SCANCODE_Q)) arrow->trans->angle -= 10;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_E)) arrow->trans->angle += 10;

			if (mint_InputCheckStatus(input, SDL_SCANCODE_W)) arrow->trans->centre->y -= 1;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_S)) arrow->trans->centre->y += 1;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_A)) arrow->trans->centre->x -= 1;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_D)) arrow->trans->centre->x += 1;

			if (mint_InputCheckStatus(input, SDL_SCANCODE_Z)) arrow->trans->flip = SDL_FLIP_NONE;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_X)) arrow->trans->flip = SDL_FLIP_HORIZONTAL;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_C)) arrow->trans->flip = SDL_FLIP_VERTICAL;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_V)) arrow->trans->flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

			mint_DisplayClearRenderer(sdlRenderer);

			mint_TextureRender(arrow);
			
			SDL_RenderPresent(sdlRenderer);
		}
	}
}

void mintTextureTTFExampleLoop()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* text = mint_TextureFromText(sdlRenderer, ttfOpenSans, "This is some test text", {0, 0, 0, 0});

	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);

			mint_TextureRender(text);
			
			SDL_RenderPresent(sdlRenderer);
		}
	}
}

void mintTextureButtonExampleLoop()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* buttons[2];

	int i;
	for (i = 0; i < 3; i++) {
		buttons[i] = mint_TextureFromPNG(sdlRenderer, "assets/img/button.png");

		mint_TextureSetupAnimMan(buttons[i], 1);
		mint_AnimCreate(buttons[i]->animMan, 0, "default", 3);
		mint_AnimDefineLinearStripFrames(mint_AnimGetByIndex(buttons[i]->animMan, 0), 100, 0);
		mint_AnimPlay(mint_AnimGetByIndex(buttons[i]->animMan, 0));

		buttons[i]->trans->x = (mint_TransGetWidth(buttons[i]->trans) + 20) * i;
	}

	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN ||
				e.type == SDL_KEYUP ||
				e.type == SDL_MOUSEMOTION ||
				e.type == SDL_MOUSEBUTTONDOWN ||
				e.type == SDL_MOUSEBUTTONUP) mint_InputUpdate(input, &e);
			    
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);

			for (i = 0; i < 3; i++) {
				mint_AnimUpdateAsButton(buttons[i]->animMan, input);
				mint_TextureRender(buttons[i]);
			}
			
			SDL_RenderPresent(sdlRenderer);
		}
	}
}

void mintTimerExampleLoop()
{
	SDL_Event e;
	char quit = 0;

	SDL_Point objectAt = { 0, 0 };
	char dir = 1;
	objectAt.x = SCREEN_WIDTH / 2;
	// timer->msPerReport = 1000;
	// timer->msSinceLastReport = 1000;

	while (!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN ||
				e.type == SDL_KEYUP ||
				e.type == SDL_MOUSEMOTION ||
				e.type == SDL_MOUSEBUTTONDOWN ||
				e.type == SDL_MOUSEBUTTONUP) mint_InputUpdate(input, &e);

			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;
		}

		mint_TimerUpdate(timer, SDL_GetTicks());

		objectAt.y += (int)(dir * timer->elapsed);

		if (objectAt.y > SCREEN_HEIGHT) {
			dir = -1;
			objectAt.y = SCREEN_HEIGHT;
		}

		if (objectAt.y < 0) {
			dir = 1;
			objectAt.y = 0;
		}

		mint_DisplayClearRenderer(sdlRenderer);
		// mint_GeomDrawRect(sdlRenderer, objectAt.x, objectAt.y, 10, 10, 0xFF0000FF);
		SDL_RenderPresent(sdlRenderer);
	}
}
