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
#include "mintSDL/maths/geom.h"
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
void texturePackerExample();

/*

	Todo:
		Fix warnings
		Fix leaks
		Make event handler
		Make animation work properly
		setX vs Xset
		Box2D debug draw
		Do scaling, this includes mass
		Do a better job making all needed math structs and functions (Move MintFloatPoint and make point/rect structs)
		Need to list all headers
		Cap fps if no vsync (And maybe in all cases)
		Make fps/other-stat counter
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
MintPhysWorld *world;

int main(int argc, char* args[])
{
#ifdef _CRTDBG_MAP_ALLOC
	// _CrtSetBreakAlloc(202);
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
	world = mint_PhysSetupWorld(0, 10);

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
	// collisionExample();
	texturePackerExample();

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
			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;

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
	mint_PhysFreeWorld(world);
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
			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;

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
			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;

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
			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_RendClearSdlRenderer(sdlRenderer);
			
			if (mint_InputCheckKey(input, SDL_SCANCODE_Q)) colour.r += 10;
			if (mint_InputCheckKey(input, SDL_SCANCODE_A)) colour.r -= 10;
			if (mint_InputCheckKey(input, SDL_SCANCODE_W)) colour.g += 10;
			if (mint_InputCheckKey(input, SDL_SCANCODE_S)) colour.g -= 10;
			if (mint_InputCheckKey(input, SDL_SCANCODE_E)) colour.b += 10;
			if (mint_InputCheckKey(input, SDL_SCANCODE_D)) colour.b -= 10;

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
			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			mint_RendClearSdlRenderer(sdlRenderer);
			
			if (mint_InputCheckKey(input, SDL_SCANCODE_Q)) alpha += 10;
			if (mint_InputCheckKey(input, SDL_SCANCODE_A)) alpha -= 10;

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

	mint_AnimCreate(texture->animMan, 0, "anim1", 4, 15);
	mint_AnimDefineLinearStripFrames(mint_AnimGetByIndex(texture->animMan, 0), 64, 1);
	mint_AnimPlay(mint_AnimGetByIndex(texture->animMan, 0));

	while (!quit)
	{
		mint_TimerUpdate(timer, (float)(SDL_GetTicks() / 1000.0));

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) mint_InputUpdate(input, &e);
			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;
		}

		mint_RendClearSdlRenderer(sdlRenderer);

		mint_TextureUpdate(texture, timer->elapsed);
		mint_TextureRender(texture);
		
		SDL_RenderPresent(sdlRenderer);
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
			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;

			if (mint_InputCheckKey(input, SDL_SCANCODE_Q)) arrow->trans->angle -= 10;
			if (mint_InputCheckKey(input, SDL_SCANCODE_E)) arrow->trans->angle += 10;

			if (mint_InputCheckKey(input, SDL_SCANCODE_W)) arrow->trans->centre.y -= 1;
			if (mint_InputCheckKey(input, SDL_SCANCODE_S)) arrow->trans->centre.y += 1;
			if (mint_InputCheckKey(input, SDL_SCANCODE_A)) arrow->trans->centre.x-= 1;
			if (mint_InputCheckKey(input, SDL_SCANCODE_D)) arrow->trans->centre.x += 1;

			if (mint_InputCheckKey(input, SDL_SCANCODE_Z)) arrow->trans->flip = SDL_FLIP_NONE;
			if (mint_InputCheckKey(input, SDL_SCANCODE_X)) arrow->trans->flip = SDL_FLIP_HORIZONTAL;
			if (mint_InputCheckKey(input, SDL_SCANCODE_C)) arrow->trans->flip = SDL_FLIP_VERTICAL;
			if (mint_InputCheckKey(input, SDL_SCANCODE_V)) arrow->trans->flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

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
			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;

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
		mint_AnimCreate(buttons[i]->animMan, 0, "default", 3, 60);
		mint_AnimDefineLinearStripFrames(mint_AnimGetByIndex(buttons[i]->animMan, 0), 100, 0);
		mint_AnimPlay(mint_AnimGetByIndex(buttons[i]->animMan, 0));

		mint_TransSetX(buttons[i]->trans, (mint_TransGetWidth(buttons[i]->trans) + 20) * i);
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
			    
			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;

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
	float speed = 1000;

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

			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;
		}

		mint_TimerUpdate(timer, (float)(SDL_GetTicks() / 1000.0));

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

	MintTexture* texture = mint_TextureFromPNG(sdlRenderer, "assets/img/ball.png");
	texture->phys = mint_PhysEnable(texture, world, 1, 3);
	float speed = 5;

	mint_PhysSetGravity(world, 0, 0);

	while (!quit)
	{
		mint_TimerUpdate(timer, (float)(SDL_GetTicks() / 1000.0));

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN ||
			    e.type == SDL_KEYUP ||
			    e.type == SDL_MOUSEMOTION ||
			    e.type == SDL_MOUSEBUTTONDOWN ||
			    e.type == SDL_MOUSEBUTTONUP) mint_InputUpdate(input, &e);

			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;
		}

		if (mint_InputCheckKey(input, SDL_SCANCODE_RIGHT)) mint_PhysApplyForce(texture->phys, speed, 0);
		if (mint_InputCheckKey(input, SDL_SCANCODE_LEFT)) mint_PhysApplyForce(texture->phys, -speed, 0);
		if (mint_InputCheckKey(input, SDL_SCANCODE_UP)) mint_PhysApplyForce(texture->phys, 0, -speed);
		if (mint_InputCheckKey(input, SDL_SCANCODE_DOWN)) mint_PhysApplyForce(texture->phys, 0, speed);

		mint_RendClearSdlRenderer(sdlRenderer);

		mint_TextureUpdate(texture, timer->elapsed);
		mint_TextureRender(texture);
		
		mint_PhysStepWorld(world, timer->elapsed);

		SDL_RenderPresent(sdlRenderer);
	}

	mint_TextureFree(texture);
}

void collisionExample()
{
	SDL_Event e;
	char quit = 0;

	srand((int)time(NULL));

	float secondsTillRegen = 0;

	SDL_Color red = { 255, 0, 0, 255 };
	SDL_Color blue = { 0, 0, 255, 255 };

	MintTexture* box1 = mint_TextureFromPNG(sdlRenderer, "assets/img/box.png");
	MintTexture* box2 = mint_TextureFromPNG(sdlRenderer, "assets/img/box.png");

	box1->phys = mint_PhysEnable(box1, world, 1, 1);
	box2->phys = mint_PhysEnable(box2, world, 1, 1);

	MintFloatPoint velo1;
	MintFloatPoint velo2;

	mint_RendSetColour(box1->rend, &red);
	mint_RendSetColour(box2->rend, &blue);

	mint_PhysSetGravity(world, 0, 5);

	while (!quit)
	{
		mint_TimerUpdate(timer, (float)(SDL_GetTicks() / 1000.0));

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN ||
			    e.type == SDL_KEYUP ||
			    e.type == SDL_MOUSEMOTION ||
			    e.type == SDL_MOUSEBUTTONDOWN ||
			    e.type == SDL_MOUSEBUTTONUP) mint_InputUpdate(input, &e);

			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;
		}

		secondsTillRegen -= timer->elapsed;
		if (secondsTillRegen <= 0) {
			secondsTillRegen = 1;

			if (rand() % 2) {
				mint_TransSetX(box1->trans, rand() % (SCREEN_WIDTH - box1->trans->_width));
				mint_TransSetY(box1->trans, (rand() % 20) + 20);

				mint_TransSetX(box2->trans, rand() % (SCREEN_WIDTH - box1->trans->_width));
				mint_TransSetY(box2->trans, SCREEN_HEIGHT - box1->trans->_height - (rand() % 20) - 20);
			} else {
				mint_TransSetX(box1->trans, 20);
				mint_TransSetY(box1->trans, rand() % (SCREEN_HEIGHT - box1->trans->_height));

				mint_TransSetX(box2->trans, SCREEN_WIDTH - box1->trans->_width - (rand() % 20) - 20);
				mint_TransSetY(box2->trans, rand() % (SCREEN_HEIGHT - box1->trans->_height));
			}

			velo1.x = (float)(box2->trans->_x - box1->trans->_x);
			velo1.y = (float)(box2->trans->_y - box1->trans->_y);
			velo2.x = (float)(box1->trans->_x - box2->trans->_x);
			velo2.y = (float)(box1->trans->_y - box2->trans->_y);

			mint_GeomNormalizeFloatPoint(&velo1, 10);
			mint_GeomNormalizeFloatPoint(&velo2, 10);

			mint_PhysSetVelocity(box1->phys, velo1.x, velo1.y);
			mint_PhysSetVelocity(box2->phys, velo2.x, velo2.y);
		}

		mint_RendClearSdlRenderer(sdlRenderer);

		mint_PhysStepWorld(world, timer->elapsed);

		mint_TextureUpdate(box1, timer->elapsed);
		mint_TextureUpdate(box2, timer->elapsed);

		mint_TextureRender(box1);
		mint_TextureRender(box2);

		SDL_RenderPresent(sdlRenderer);
	}

	mint_TextureFree(box1);
	mint_TextureFree(box2);
}

void texturePackerExample()
{
	SDL_Event e;
	char quit = 0;

	// TODO(jeru): Change the 10 to a more relevant number
	const int ANIMS = 10;

	MintTexture* player[ANIMS];

	int i;
	for (i = 0; i < ANIMS; i++) {
		player[i] = mint_TextureFromPNG(sdlRenderer, "assets/img/player_blue.png");
		mint_AnimCreateFromXML(player[i]->animMan, "assets/img/player_blue.xml");
		
		mint_AnimPlay(mint_AnimGetByIndex(player[i]->animMan, i));
		mint_AnimGetByIndex(player[i]->animMan, i)->loop = 1;

		mint_TransSetX(player[i]->trans, 50 * i);
	}

	while (!quit)
	{
		mint_TimerUpdate(timer, (float)(SDL_GetTicks() / 1000.0));
		
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN ||
			    e.type == SDL_KEYUP ||
			    e.type == SDL_MOUSEMOTION ||
			    e.type == SDL_MOUSEBUTTONDOWN ||
			    e.type == SDL_MOUSEBUTTONUP) mint_InputUpdate(input, &e);

			if (e.type == SDL_QUIT || mint_InputCheckKey(input, SDL_SCANCODE_ESCAPE)) quit = 1;
		}

		mint_RendClearSdlRenderer(sdlRenderer);
		
		for (i = 0; i < ANIMS; i++) {
			mint_TextureUpdate(player[i], timer->elapsed);
			mint_TextureRender(player[i]);
		}

		SDL_RenderPresent(sdlRenderer);
	}

	for (i = 0; i < ANIMS; i++) mint_TextureFree(player[i]);
}