#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "mintSDL/input.h"
#include "mintSDL/timer.h"
#include "mintSDL/display/display.h"
#include "mintSDL/display/anim.h"
#include "mintSDL/display/geom.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/maths/phys.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void close();
void gameLoop();
void geomExample();
void mintTextureExample();
void setColourInputExample();
void setAlphaInputExample();
void animationExample();
void transformExample();
void textExample();
void buttonExample();
void timerExample();
void physExample();

/*
	Todo (Actually do these):
		Cap fps if no vsync (And maybe in all cases)
		Move maths stuff into maths directory
		Consider changing Display to Rend
		Consider creating setup and free for things like MintTrans and MintRend
		Make batch file to copy bin files
		Make fps/other-stat counter
		Consider pointer vs non-pointer for structs
		Move MintFloatPoint and make point structs
		Look into how the optimizer cleans up rename variables
		Look into better reletive paths for includes
		Figure out if I need unsigned chars for colour and alpha
		Consider moving MintTrans to maths directory

	Notes:
		Centre point is going to break when animations happen (They did)
*/

SDL_Window* sdlWindow = NULL;
SDL_Renderer* sdlRenderer = NULL;
TTF_Font *ttfOpenSans = NULL;
MintInput *input;
MintFrameTimer *timer;

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
			sdlRenderer = mint_DisplayCreateRenderer(sdlWindow, 1);
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
	// geomExample();
	// mintTextureExample();
	// setColourInputExample();
	// setAlphaInputExample();
	// animationExample();
	// transformExample();
	// textExample();
	// buttonExample();
	timerExample();
	// physExample();

	close();

#ifdef _CRTDBG_MAP_ALLOC
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}

void gameLoop()
{
	SDL_Event e;
	char quit = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
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
	mint_TimerFree(timer);
	TTF_CloseFont(ttfOpenSans);

	SDL_Quit();
}

void geomExample()
{
	SDL_Event e;
	char quit = 0;

	SDL_Color colour0 = { 255, 0, 0, 255 };
	SDL_Color colour1 = { 255, 0, 255, 255 };

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);
			
			mint_GeomDrawRect(sdlRenderer, 0, 0, 100, 100, &colour0);
			mint_GeomDrawLine(sdlRenderer, 100, 100, 200, 200, &colour0);
			mint_GeomDrawLine(sdlRenderer, 200, 200, 300, 100, &colour0);
			mint_GeomDrawRect(sdlRenderer, 300, 50, 100, 50, &colour1);
			
			SDL_RenderPresent(sdlRenderer);
		}
	}
}

void mintTextureExample()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* texture = mint_TextureFromPNG(sdlRenderer, "assets/img/pngSplash.png");
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);
			
			mint_TextureRender(texture);
			
			SDL_RenderPresent(sdlRenderer);
		}
	}

	mint_TextureFree(texture);
}

void setColourInputExample()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* texture = mint_TextureFromPNG(sdlRenderer, "assets/img/pngSplash.png");
	SDL_Color colour = { 255, 255, 255, 0 };
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
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

	mint_TextureFree(texture);
}

void setAlphaInputExample()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* texture = mint_TextureFromPNG(sdlRenderer, "assets/img/pngSplash.png");
	unsigned char alpha = 255;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
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

	mint_TextureFree(texture);
}

void animationExample()
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
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);

			mint_TextureRender(texture);
			mint_AnimNextFrame(texture->animMan);
			
			SDL_RenderPresent(sdlRenderer);
		}
	}

	mint_TextureFree(texture);
}

void transformExample()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* arrow = mint_TextureFromPNG(sdlRenderer, "assets/img/arrow.png");

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
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

	mint_TextureFree(arrow);
}

void textExample()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* text = mint_TextureFromText(sdlRenderer, ttfOpenSans, "This is some test text", {0, 0, 0, 0});

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_DisplayClearRenderer(sdlRenderer);

			mint_TextureRender(text);
			
			SDL_RenderPresent(sdlRenderer);
		}
	}

	mint_TextureFree(text);
}

void buttonExample()
{
	SDL_Event e;
	char quit = 0;

	MintTexture* buttons[3];

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
		while (SDL_PollEvent(&e) != 0)
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

	for (i = 0; i < 3; i++) mint_TextureFree(buttons[i]);
}

void timerExample()
{
	SDL_Event e;
	char quit = 0;

	SDL_Point objectAt = { 0, 0 };
	SDL_Color colour = { 255, 0, 0, 255 };
	char dir = 1;
	double speed = 1000;

	objectAt.x = SCREEN_WIDTH / 2;
	timer->secondsPerReport = 1;
	timer->secondsSinceLastReport = 1;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN ||
			    e.type == SDL_KEYUP ||
	        e.type == SDL_MOUSEMOTION ||
			    e.type == SDL_MOUSEBUTTONDOWN ||
			    e.type == SDL_MOUSEBUTTONUP) mint_InputUpdate(input, &e);

			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;
		}

		mint_TimerUpdate(timer, SDL_GetTicks() / 1000.0);

		objectAt.y += (int)(dir * timer->elapsed * speed);

		if (objectAt.y > SCREEN_HEIGHT) {
			dir = -1;
			objectAt.y = SCREEN_HEIGHT;
		}

		if (objectAt.y < 0) {
			dir = 1;
			objectAt.y = 0;
		}

		mint_DisplayClearRenderer(sdlRenderer);
		mint_GeomDrawRect(sdlRenderer, objectAt.x, objectAt.y, 10, 10, &colour);
		SDL_RenderPresent(sdlRenderer);
	}
}

void physExample()
{
	SDL_Event e;
	char quit = 0;

	double maxVelocity = 400;
	double velocityChange = maxVelocity * 10;
	double drag = maxVelocity * 10;

	MintTexture* texture = mint_TextureFromPNG(sdlRenderer, "assets/img/ball.png");
	texture->phys->drag = { drag, drag };
	texture->phys->maxVelocity = { maxVelocity, maxVelocity };

	while (!quit)
	{
		mint_TimerUpdate(timer, SDL_GetTicks() / 1000.0);

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN ||
			    e.type == SDL_KEYUP ||
			    e.type == SDL_MOUSEMOTION ||
			    e.type == SDL_MOUSEBUTTONDOWN ||
			    e.type == SDL_MOUSEBUTTONUP) mint_InputUpdate(input, &e);

			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;
		}

		texture->phys->accel.x = 0;
		texture->phys->accel.y = 0;
		if (mint_InputCheckStatus(input, SDL_SCANCODE_LEFT)) texture->phys->accel.x -= velocityChange;
		if (mint_InputCheckStatus(input, SDL_SCANCODE_RIGHT)) texture->phys->accel.x += velocityChange;
		if (mint_InputCheckStatus(input, SDL_SCANCODE_UP)) texture->phys->accel.y -= velocityChange;
		if (mint_InputCheckStatus(input, SDL_SCANCODE_DOWN)) texture->phys->accel.y += velocityChange;
		
		mint_PhysUpdate(texture->phys, timer->elapsed);
		// printf("Velo: %lf %lf elapsed: %f\n", texture->phys->velocity.x, texture->phys->velocity.y, timer->elapsed);

		mint_DisplayClearRenderer(sdlRenderer);

		mint_TextureRender(texture);

		SDL_RenderPresent(sdlRenderer);
	}
}
