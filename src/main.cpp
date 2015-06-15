const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 832;

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#ifdef _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#include <stdio.h>
#include <string>
#include <time.h>
#include <SDL.h>
#include "mintSDL/display/anim.h"
#include "mintSDL/display/draw.h"
#include "mintSDL/display/rend.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/display/tilemap.h"
#include "mintSDL/maths/phys.h"
#include "mintSDL/maths/geom.h"
#include "mintSDL/util/input.h"
#include "mintSDL/util/timer.h"
#include "mintSDL/system.h"

void gameExample(MintSystem* sys);
void drawExample(MintSystem* sys);
void mintTextureExample(MintSystem* sys);
void setColourInputExample(MintSystem* sys);
void setAlphaInputExample(MintSystem* sys);
void animationExample(MintSystem* sys);
void transformExample(MintSystem* sys);
void textExample(MintSystem* sys);
void buttonExample(MintSystem* sys);
void timerExample(MintSystem* sys);
void physicsExample(MintSystem* sys);
void collisionExample(MintSystem* sys);
void texturePackerExample(MintSystem* sys);
// void playerExample(MintSystem* sys);
// void tilemapExample(MintSystem* sys);

/*

	Todo:
		Add screen width/height to system
		Get rid of calloc lol
		Make better font system
		Make event handler
		Build collision on tilemap
		Make array type?
		Clip, rect, quad, names?
		Abstract texture loading?
		Local/global transform
		Add magic number defines
		Optimize XML
		setX vs Xset
		Box2D debug draw
		Do scaling, this includes mass
		Do a better job making all needed math structs and functions (Move MintFloatPoint and make point/rect structs)
		Need to list all headers
		Make fps/other-stat counter
		Make auto-tester
		Linux?
		Mingw?

	Notes:
		Centre point is going to break when animations happen (They did)

*/

MintSystem* sys;

int main(int argc, char* args[])
{
#ifdef _CRTDBG_MAP_ALLOC
	// _CrtSetBreakAlloc(202);
#endif

	sys = mint_SystemSetup();

	// sys->start = &gameExample;
	// sys->start = &drawExample;
	// sys->start = &mintTextureExample;
	// sys->start = &setColourInputExample;
	// sys->start = &setAlphaInputExample;
	// sys->start = &animationExample;
	// sys->start = &transformExample;
	// sys->start = &textExample;
	// sys->start = &buttonExample;
	// sys->start = &timerExample;
	// sys->start = &physicsExample;
	// sys->start = &collisionExample;
	sys->start = &texturePackerExample;
	// sys->start = &tilemapExample;

	mint_SystemInit(sys);

	return 0;
}

void gameExample(MintSystem* sys)
{
	for(;;)
	{
		mint_SystemPreUpdate(sys);
		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);
		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}
}

void drawExample(MintSystem* sys)
{
	SDL_Color colour0 = { 255, 0, 0, 255 };
	SDL_Color colour1 = { 255, 0, 255, 255 };

	for(;;)
	{
		mint_SystemPreUpdate(sys);
		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);
	
		mint_DrawRect(sys, 0, 0, 100, 100, &colour0);
		mint_DrawLine(sys, 100, 100, 200, 200, &colour0);
		mint_DrawLine(sys, 200, 200, 300, 100, &colour0);
		mint_DrawRect(sys, 300, 50, 100, 50, &colour1);

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}
}

void mintTextureExample(MintSystem* sys)
{
	MintTexture* texture = mint_TextureFromPNG(sys, "assets/img/pngSplash.png");

	for(;;)
	{
		mint_SystemPreUpdate(sys);
		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		mint_TextureRender(texture);

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}

	mint_TextureFree(texture);
}

void setColourInputExample(MintSystem* sys)
{
	MintTexture* texture = mint_TextureFromPNG(sys, "assets/img/pngSplash.png");

	SDL_Color colour = { 255, 255, 255, 0 };

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_Q)) colour.r += 10;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_A)) colour.r -= 10;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_W)) colour.g += 10;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_S)) colour.g -= 10;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_E)) colour.b += 10;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_D)) colour.b -= 10;
		mint_TransSetColour(texture->trans, &colour);

		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		mint_TextureRender(texture);
			
		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}

	mint_TextureFree(texture);
}

void setAlphaInputExample(MintSystem* sys)
{
	MintTexture* texture = mint_TextureFromPNG(sys, "assets/img/pngSplash.png");

	unsigned char alpha = 255;

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_Q)) alpha += 10;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_A)) alpha -= 10;
		mint_TransSetAlpha(texture->trans, alpha);

		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		mint_TextureRender(texture);

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}

	mint_TextureFree(texture);
}

void animationExample(MintSystem* sys)
{
	MintTexture* texture = mint_TextureFromPNG(sys, "assets/img/animation.png");
	mint_AnimManInit(texture->animMan, 1);

	mint_AnimCreate(texture->animMan, 0, "anim1", 4, 15);
	mint_AnimDefineLinearStripFrames(mint_AnimGetByIndex(texture->animMan, 0), 64, 1);
	mint_AnimPlay(mint_AnimGetByIndex(texture->animMan, 0));

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		mint_TextureUpdate(texture, sys->elapsed);

		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		mint_TextureRender(texture);

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}

	mint_TextureFree(texture);
}

void transformExample(MintSystem* sys)
{
	MintTexture* arrow = mint_TextureFromPNG(sys, "assets/img/arrow.png");

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_Q)) arrow->trans->angle -= 10;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_E)) arrow->trans->angle += 10;

		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_W)) arrow->trans->centre.y -= 1;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_S)) arrow->trans->centre.y += 1;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_A)) arrow->trans->centre.x-= 1;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_D)) arrow->trans->centre.x += 1;

		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_Z)) arrow->trans->flip = SDL_FLIP_NONE;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_X)) arrow->trans->flip = SDL_FLIP_HORIZONTAL;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_C)) arrow->trans->flip = SDL_FLIP_VERTICAL;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_V)) arrow->trans->flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		mint_TextureRender(arrow);

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}

	mint_TextureFree(arrow);
}

void textExample(MintSystem* sys)
{
	MintTexture* text = mint_TextureFromText(sys, sys->font, "This is some test text", {0, 0, 0, 0});

	for(;;)
	{
		mint_SystemPreUpdate(sys);
		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		mint_TextureRender(text);

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}

	mint_TextureFree(text);
}

void buttonExample(MintSystem* sys)
{
	MintTexture* buttons[3];

	int i;
	for (i = 0; i < 3; i++) {
		buttons[i] = mint_TextureFromPNG(sys, "assets/img/button.png");

		mint_AnimManInit(buttons[i]->animMan, 1);
		mint_AnimCreate(buttons[i]->animMan, 0, "default", 3, 60);
		mint_AnimDefineLinearStripFrames(mint_AnimGetByIndex(buttons[i]->animMan, 0), 100, 0);
		mint_AnimPlay(mint_AnimGetByIndex(buttons[i]->animMan, 0));

		mint_TransSetX(buttons[i]->trans, (mint_TransGetWidth(buttons[i]->trans) + 20) * i);
	}

	for(;;)
	{
		mint_SystemPreUpdate(sys);
		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		for (i = 0; i < 3; i++) {
			mint_AnimUpdateAsButton(buttons[i]->animMan, sys->input);
			mint_TextureRender(buttons[i]);
		}

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}

	for (i = 0; i < 3; i++) mint_TextureFree(buttons[i]);
}

void timerExample(MintSystem* sys)
{
	SDL_Point objectAt = { 0, 0 };
	SDL_Color colour = { 255, 0, 0, 255 };
	char dir = 1;
	float speed = 1000;

	objectAt.x = SCREEN_WIDTH / 2;
	sys->timer->secondsPerReport = 1;
	sys->timer->secondsSinceLastReport = 1;

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		objectAt.y += (int)(dir * sys->elapsed * speed);

		if (objectAt.y > SCREEN_HEIGHT) {
			dir = -1;
			objectAt.y = SCREEN_HEIGHT;
		}

		if (objectAt.y < 0) {
			dir = 1;
			objectAt.y = 0;
		}

		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		mint_DrawRect(sys, objectAt.x, objectAt.y, 10, 10, &colour);

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}
}

void physicsExample(MintSystem* sys)
{
	MintTexture* texture = mint_TextureFromPNG(sys, "assets/img/ball.png");
	mint_PhysEnable(texture, sys->world, 1, 3);
	float speed = 5;

	mint_PhysSetGravity(sys->world, 0, 0);

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_RIGHT)) mint_PhysApplyForce(texture->phys, speed, 0);
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_LEFT)) mint_PhysApplyForce(texture->phys, -speed, 0);
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_UP)) mint_PhysApplyForce(texture->phys, 0, -speed);
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_DOWN)) mint_PhysApplyForce(texture->phys, 0, speed);

		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		mint_TextureUpdate(texture, sys->elapsed);
		mint_TextureRender(texture);

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}

	mint_TextureFree(texture);
}

void collisionExample(MintSystem* sys)
{
	srand((int)time(NULL));

	float secondsTillRegen = 0;

	SDL_Color red = { 255, 0, 0, 255 };
	SDL_Color blue = { 0, 0, 255, 255 };

	MintTexture* box1 = mint_TextureFromPNG(sys, "assets/img/box.png");
	MintTexture* box2 = mint_TextureFromPNG(sys, "assets/img/box.png");

	mint_PhysEnable(box1, sys->world, 1, 1);
	mint_PhysEnable(box2, sys->world, 1, 1);

	MintFloatPoint velo1;
	MintFloatPoint velo2;

	mint_TransSetColour(box1->trans, &red);
	mint_TransSetColour(box2->trans, &blue);

	mint_PhysSetGravity(sys->world, 0, 5);

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		secondsTillRegen -= sys->elapsed;
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

		mint_SystemUpdate(sys);

		mint_TextureUpdate(box1, sys->elapsed);
		mint_TextureUpdate(box2, sys->elapsed);

		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		mint_TextureRender(box1);
		mint_TextureRender(box2);

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}

	mint_TextureFree(box1);
	mint_TextureFree(box2);
}

void texturePackerExample(MintSystem* sys)
{
	// TODO(jeru): Change the 10 to a more relevant number
	const int ANIMS = 10;

	MintTexture* player[ANIMS];

	int i;
	for (i = 0; i < ANIMS; i++) {
		player[i] = mint_TextureFromPNG(sys, "assets/img/player_blue.png");
		mint_AnimCreateFromXML(player[i]->animMan, "assets/img/player_blue.xml");
		
		mint_AnimPlay(mint_AnimGetByIndex(player[i]->animMan, i));
		mint_AnimGetByIndex(player[i]->animMan, i)->loop = 1;

		mint_TransSetX(player[i]->trans, 50 * i);
	}

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		for (i = 0; i < ANIMS; i++) mint_TextureUpdate(player[i], sys->elapsed);

		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		for (i = 0; i < ANIMS; i++) mint_TextureRender(player[i]);

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}
	
	for (i = 0; i < ANIMS; i++) mint_TextureFree(player[i]);
}
/*
void playerExample(MintSystem* sys)
{
	MintTexture* player;
	int i;
	char left;
	char right;
	char up;
	char down;

	char animStr[99];
	char dirStr = GEOM_RIGHT;

	player = mint_TextureFromPNG(sys, "assets/img/player_blue.png");
	mint_PhysEnable(player, world, 1, 1);
	mint_PhysSetGravity(world, 0, 0);
	mint_PhysSetDamping(player->phys, 50);
	
	mint_AnimCreateFromXML(player->animMan, "assets/img/player_blue.xml");
	for (i = 0; i < player->animMan->totalAnims; i++) mint_AnimGetByIndex(player->animMan, i)->loop = 1;

	mint_AnimPlay(mint_AnimGetByName(player->animMan, "player_blue_SMG_downRight_running_"));

	mint_TransSetX(player->trans, 200);
	mint_TransSetY(player->trans, 200);

	while (!quit) {
		
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN ||
			    e.type == SDL_KEYUP ||
			    e.type == SDL_MOUSEMOTION ||
			    e.type == SDL_MOUSEBUTTONDOWN ||
			    e.type == SDL_MOUSEBUTTONUP) mint_InputUpdate(input, &e);

			if (e.type == SDL_QUIT || mint_InputCheckKey(sys->input, SDL_SCANCODE_ESCAPE)) quit = 1;
		}

		left = mint_InputCheckKey(sys->input, SDL_SCANCODE_LEFT);
		right = mint_InputCheckKey(sys->input, SDL_SCANCODE_RIGHT);
		up = mint_InputCheckKey(sys->input, SDL_SCANCODE_UP);
		down = mint_InputCheckKey(sys->input, SDL_SCANCODE_DOWN);

		if (left) mint_PhysSetVelocity(player->phys, -5, mint_PhysGetVelocity(player->phys).y);
		if (right) mint_PhysSetVelocity(player->phys, 5, mint_PhysGetVelocity(player->phys).y);
		if (up) mint_PhysSetVelocity(player->phys, mint_PhysGetVelocity(player->phys).x, -5);
		if (down) mint_PhysSetVelocity(player->phys, mint_PhysGetVelocity(player->phys).x, 5);

		strcpy(animStr, "player_blue_SMG_");

		if (up && right) {
			strcat(animStr, "upRight");
			player->trans->flip = SDL_FLIP_NONE;
		} else if (down && right) {
			strcat(animStr, "downRight");
			player->trans->flip = SDL_FLIP_NONE;
		} else if (up && left) {
			strcat(animStr, "upRight");
			player->trans->flip = SDL_FLIP_HORIZONTAL;
		} else if (down && left) {
			strcat(animStr, "downRight");
			player->trans->flip = SDL_FLIP_HORIZONTAL;
		} else if (left) {
			strcat(animStr, "right");
			player->trans->flip = SDL_FLIP_HORIZONTAL;
			dirStr = GEOM_LEFT;
		} else if (right) {
			strcat(animStr, "right");
			player->trans->flip = SDL_FLIP_NONE;
			dirStr = GEOM_RIGHT;
		} else if (up) {
			strcat(animStr, "up");
			player->trans->flip = SDL_FLIP_NONE;
			dirStr = GEOM_UP;
		} else if (down) {
			strcat(animStr, "down");
			player->trans->flip = SDL_FLIP_NONE;
			dirStr = GEOM_DOWN;
		} else {
			if (dirStr == GEOM_LEFT) {
				strcat(animStr, "right");
				player->trans->flip = SDL_FLIP_HORIZONTAL;
			} else {
				player->trans->flip = SDL_FLIP_NONE;
			}

			if (dirStr == GEOM_RIGHT) strcat(animStr, "right");
			if (dirStr == GEOM_UP) strcat(animStr, "up");
			if (dirStr == GEOM_DOWN) strcat(animStr, "down");
		}

		strcat(animStr, up || down || left || right ? "_running_" : "_standing_");

		mint_AnimPlay(mint_AnimGetByName(player->animMan, animStr));

// Pre render
		
		mint_PhysStepWorld(world, sys->elapsed);
		mint_TextureUpdate(player, sys->elapsed);
		mint_TextureRender(player);

// Post render
		if ((1.0 / 60.0 * 1000.0) - (SDL_GetTicks() - timer->ticks) > 0) SDL_Delay((int)((1.0 / 60.0 * 1000.0) - (SDL_GetTicks() - timer->ticks)));
	}

	mint_TextureFree(player);
}

void tilemapExample(MintSystem* sys)
{
	
	MintTilemap* tilemap = mint_TilemapCreate(sys, "assets/img/tilemap.png", 64, 64, 0);
	mint_RendFullScreen(sdlWindow, 1);

	mint_TilemapGenerateFromTiled(tilemap, "assets/map/test1.tmx");

	while (!quit) {

		if (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN ||
			    e.type == SDL_KEYUP ||
			    e.type == SDL_MOUSEMOTION ||
			    e.type == SDL_MOUSEBUTTONDOWN ||
			    e.type == SDL_MOUSEBUTTONUP) mint_InputUpdate(input, &e);

			if (e.type == SDL_QUIT || mint_InputCheckKey(sys->input, SDL_SCANCODE_ESCAPE)) quit = 1;
		}

// Pre render

		mint_TilemapRenderLayer(tilemap, 0);
		mint_TilemapRenderLayer(tilemap, 1);
		mint_TilemapRenderLayer(tilemap, 2);
		mint_TilemapRenderLayer(tilemap, 3);
		// mint_TilemapRenderLayer(tilemap, 4);

// Post render
	}

	mint_TilemapFree(tilemap);
}
*/