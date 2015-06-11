#define _CRTDBG_MAP_ALLOC

#ifdef _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#include <stdio.h>
#include <string>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "mintSDL/display/anim.h"
#include "mintSDL/display/draw.h"
#include "mintSDL/display/rend.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/maths/phys.h"
#include "mintSDL/util/input.h"
#include "mintSDL/util/timer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void close();
void gameLoop();
void drawExample();
void mintTextureExample();
void setColourInputExample();
void setAlphaInputExample();
void animationExample();
void transformExample();
void textExample();
void buttonExample();
void timerExample();
void physicsExample();
void collisionExample();

/*

	Todo:
		Do scaling, this includes mass
		Add clamp phys.cpp#67 also maybe min and max
		Need to list all headers
		Figure out what to do about subpixels
		Remove quad from mint_TextureRender
		Make animation work properly
		Create update functions
		Cap fps if no vsync (And maybe in all cases)
		Make fps/other-stat counter
		Move MintFloatPoint and make point/rect structs
		Make auto-tester
		Linux?
		Mingw?

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
#ifdef _CRTDBG_MAP_ALLOC
	// _CrtSetBreakAlloc(112);
#endif

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
			sdlRenderer = mint_RendCreateSdlRenderer(sdlWindow, 1);
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
	// drawExample();
	// mintTextureExample();
	// setColourInputExample();
	// setAlphaInputExample();
	// animationExample();
	// transformExample();
	// textExample();
	// buttonExample();
	// timerExample();
	// physicsExample();
	collisionExample();

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

			mint_RendClearSdlRenderer(sdlRenderer);
			
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

void drawExample()
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

			mint_RendClearSdlRenderer(sdlRenderer);
			
			mint_DrawRect(sdlRenderer, 0, 0, 100, 100, &colour0);
			mint_DrawLine(sdlRenderer, 100, 100, 200, 200, &colour0);
			mint_DrawLine(sdlRenderer, 200, 200, 300, 100, &colour0);
			mint_DrawRect(sdlRenderer, 300, 50, 100, 50, &colour1);
			
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

			mint_RendClearSdlRenderer(sdlRenderer);
			
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

			mint_RendClearSdlRenderer(sdlRenderer);
			
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

			mint_RendClearSdlRenderer(sdlRenderer);
			
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
	mint_AnimManInit(texture->animMan, 1);

	mint_AnimCreate(texture->animMan, 0, "anim1", 4);
	mint_AnimDefineLinearStripFrames(mint_AnimGetByIndex(texture->animMan, 0), 64, 1);
	mint_AnimPlay(mint_AnimGetByIndex(texture->animMan, 0));

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckStatus(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_RendClearSdlRenderer(sdlRenderer);

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

			if (mint_InputCheckStatus(input, SDL_SCANCODE_W)) arrow->trans->centre.y -= 1;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_S)) arrow->trans->centre.y += 1;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_A)) arrow->trans->centre.x-= 1;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_D)) arrow->trans->centre.x += 1;

			if (mint_InputCheckStatus(input, SDL_SCANCODE_Z)) arrow->trans->flip = SDL_FLIP_NONE;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_X)) arrow->trans->flip = SDL_FLIP_HORIZONTAL;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_C)) arrow->trans->flip = SDL_FLIP_VERTICAL;
			if (mint_InputCheckStatus(input, SDL_SCANCODE_V)) arrow->trans->flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

			mint_RendClearSdlRenderer(sdlRenderer);

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

			mint_RendClearSdlRenderer(sdlRenderer);

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

		mint_AnimManInit(buttons[i]->animMan, 1);
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

			mint_RendClearSdlRenderer(sdlRenderer);

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

		mint_RendClearSdlRenderer(sdlRenderer);
		mint_DrawRect(sdlRenderer, objectAt.x, objectAt.y, 10, 10, &colour);
		SDL_RenderPresent(sdlRenderer);
	}
}

void physicsExample()
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
		
		// printf("Velo: %lf %lf elapsed: %f\n", texture->phys->velocity.x, texture->phys->velocity.y, timer->elapsed);

		mint_RendClearSdlRenderer(sdlRenderer);

		mint_TextureUpdate(texture, timer->elapsed);
		mint_TextureRender(texture);

		SDL_RenderPresent(sdlRenderer);
	}

	mint_TextureFree(texture);
}

void collisionExample()
{
	SDL_Event e;
	char quit = 0;

	double secondsTillRegen = 0;

	SDL_Color red = { 255, 0, 0, 255 };
	SDL_Color blue = { 0, 0, 255, 255 };

	MintTexture* box1 = mint_TextureFromPNG(sdlRenderer, "assets/img/box.png");
	box1->phys->drag = { 200, 200 };

	MintTexture* box2 = mint_TextureFromPNG(sdlRenderer, "assets/img/box.png");
	box2->phys->drag = { 200, 200 };

	mint_RendSetColour(box1->rend, &red);
	mint_RendSetColour(box2->rend, &blue);

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

		secondsTillRegen -= timer->elapsed;
		if (secondsTillRegen <= 0) {
			secondsTillRegen = 1.5;

			if (rand() % 2) {
				box1->trans->x = rand() % (SCREEN_WIDTH - box1->trans->_width);
				box1->trans->y = (rand() % 20) + 20;

				box2->trans->x = rand() % (SCREEN_WIDTH - box1->trans->_width);
				box2->trans->y = SCREEN_HEIGHT - box1->trans->_height - (rand() % 20) - 20;
			} else {
				box1->trans->x = 20;
				box1->trans->y = rand() % (SCREEN_HEIGHT - box1->trans->_height);

				box2->trans->x = SCREEN_WIDTH - box1->trans->_width - (rand() % 20) - 20;
				box2->trans->y = rand() % (SCREEN_HEIGHT - box1->trans->_height);
			}

			box1->phys->velocity.x = box2->trans->x - box1->trans->x;
			box1->phys->velocity.y = box2->trans->y - box1->trans->y;
			box2->phys->velocity.x = box1->trans->x - box2->trans->x;
			box2->phys->velocity.y = box1->trans->y - box2->trans->y;

			box1->phys->restitution = (rand() % 25) / 100.0 + .25;
			box2->phys->restitution = (rand() % 25) / 100.0 + .25;
		}

		if (box1->trans->x < 0) {
			box1->trans->x = 0;
			box1->phys->velocity.x *= -1;
		} else if (box1->trans->x > SCREEN_WIDTH - box1->trans->_width) {
			box1->trans->x = SCREEN_WIDTH - box1->trans->_width;
			box1->phys->velocity.x *= -1;
		}

		if (box1->trans->y < 0) {
			box1->trans->y = 0;
			box1->phys->velocity.y *= -1;
		} else if (box1->trans->y > SCREEN_HEIGHT - box1->trans->_height) {
			box1->trans->y = SCREEN_HEIGHT - box1->trans->_height;
			box1->phys->velocity.y *= -1;
		}

		if (box2->trans->x < 0) {
			box2->trans->x = 0;
			box2->phys->velocity.x *= -1;
		} else if (box2->trans->x > SCREEN_WIDTH - box2->trans->_width) {
			box2->trans->x = SCREEN_WIDTH - box2->trans->_width;
			box2->phys->velocity.x *= -1;
		}

		if (box2->trans->y < 0) {
			box2->trans->y = 0;
			box2->phys->velocity.y *= -1;
		} else if (box2->trans->y > SCREEN_HEIGHT - box2->trans->_height) {
			box2->trans->y = SCREEN_HEIGHT - box2->trans->_height;
			box2->phys->velocity.y *= -1;
		}

		mint_RendClearSdlRenderer(sdlRenderer);

		mint_TextureUpdate(box1, timer->elapsed);
		mint_TextureUpdate(box2, timer->elapsed);

		mint_PhysCollideRectRect(box1->phys, box2->phys);
		// mint_PhysCollideRectRect(box2->phys, box1->phys);

		mint_TextureRender(box1);
		mint_TextureRender(box2);

		SDL_RenderPresent(sdlRenderer);
	}

	mint_TextureFree(box1);
	mint_TextureFree(box2);
}