/*
	Todo major:
		Hitbox changes(offset only)
		Pathfinding
		Pooling
		Textfields
		Gamepad support
		Centre point/sizes is going to break when animations happen (They did)

	Todo minor:
		Debugger
		Reset totalTextures
		Remove elapsed
		Add screen width/height to system
		Get rid of calloc lol
		Make better font system
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

*/

#define WINDOWS
#define VISUAL_STUDIOS_DEBUGGING
// #define TEST_GAME

#ifdef WINDOWS
	#ifdef VISUAL_STUDIOS_DEBUGGING
		#define _CRT_SECURE_NO_WARNINGS
		#define _CRTDBG_MAP_ALLOC
		#include <stdlib.h>
		#include <crtdbg.h>
	#endif
#endif

#include <stdio.h>
#include <string>
#include <time.h>
#include <SDL.h>
#include "game/game.h"
#include "mintSDL/display/anim.h"
#include "mintSDL/display/draw.h"
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
void playerExample(MintSystem* sys);
void tilemapExample(MintSystem* sys);
void systemExample(MintSystem* sys);

MintSystem* sys;

int main(int argc, char* args[])
{
#ifdef _CRTDBG_MAP_ALLOC
	// _CrtSetBreakAlloc(202);
#endif

#ifdef TEST_GAME
	return gameMain(argc, args);
#endif

	sys = mint_SystemSetup(0);
	mint_SystemAddFont(sys, "assets/font/OpenSansRegular.ttf");
	// sys->debugDraw = 1;

	// sys->start = &gameExample;
	// sys->start = &drawExample;
	sys->start = &mintTextureExample;
	// sys->start = &setColourInputExample;
	// sys->start = &setAlphaInputExample;
	// sys->start = &animationExample;
	// sys->start = &transformExample;
	// sys->start = &textExample;
	// sys->start = &buttonExample;
	// sys->start = &timerExample;
	// sys->start = &physicsExample;
	// sys->start = &collisionExample;
	// sys->start = &texturePackerExample;
	// sys->start = &playerExample;
	// sys->start = &tilemapExample;
	// sys->start = &systemExample;

	mint_SystemInit(sys, 1);

	return 0;
}

void gameExample(MintSystem* sys)
{
	for(;;)
	{
		// mint_SystemPreUpdate(sys);
		mint_SystemUpdate(sys);
		// mint_SystemPostUpdate(sys);
		// mint_SystemPreDraw(sys);
		mint_SystemDraw(sys);
		// mint_SystemPostDraw(sys);
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
		mint_TextureSetColour(texture, &colour);

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
		mint_TextureSetAlpha(texture, alpha);

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
	mint_AnimInit(texture, 1);

	mint_AnimCreate(texture, 0, "anim1", 4, 15);
	mint_AnimDefineLinearStripFrames(mint_AnimGetByIndex(texture, 0), 64, 1);
	mint_AnimPlay(mint_AnimGetByIndex(texture, 0));

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		mint_TextureUpdate(texture, sys->timer->elapsed);

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

		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_Q)) arrow->angle -= 10;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_E)) arrow->angle += 10;

		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_W)) arrow->centre.y -= 1;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_S)) arrow->centre.y += 1;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_A)) arrow->centre.x-= 1;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_D)) arrow->centre.x += 1;

		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_Z)) arrow->flip = SDL_FLIP_NONE;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_X)) arrow->flip = SDL_FLIP_HORIZONTAL;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_C)) arrow->flip = SDL_FLIP_VERTICAL;
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_V)) arrow->flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

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
	MintTexture* text = mint_TextureFromNothing(sys);

	for(;;)
	{
		mint_SystemUpdate(sys);

		mint_TextureLoadText(text, sys->fonts[0], "Test text", { 0, 0, 0, 0 });

		mint_SystemDraw(sys);

		mint_TextureRender(text);
	}

	mint_TextureFree(text);
}

void buttonExample(MintSystem* sys)
{
	MintTexture* buttons[3];

	int i;
	for (i = 0; i < 3; i++) {
		buttons[i] = mint_TextureFromPNG(sys, "assets/img/button.png");

		mint_AnimInit(buttons[i], 1);
		mint_AnimCreate(buttons[i], 0, "default", 3, 60);
		mint_AnimDefineLinearStripFrames(mint_AnimGetByIndex(buttons[i], 0), 100, 0);
		mint_AnimPlay(mint_AnimGetByIndex(buttons[i], 0));

		mint_TextureSetX(buttons[i], (buttons[i]->width + 20) * i);
	}

	for(;;)
	{
		mint_SystemPreUpdate(sys);
		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		for (i = 0; i < 3; i++) {
			mint_AnimUpdateAsButton(buttons[i], sys->input);
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

	objectAt.x = sys->gameWidth / 2;
	sys->timer->secondsPerReport = 1;
	sys->timer->secondsSinceLastReport = 1;

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		objectAt.y += (int)(dir * sys->timer->elapsed * speed);

		if (objectAt.y > sys->gameHeight) {
			dir = -1;
			objectAt.y = sys->gameHeight;
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
	mint_PhysEnable(texture, 1, 3);
	float speed = 5;

	mint_PhysSetGravity(sys, 0, 0);

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_RIGHT)) mint_PhysApplyForce(texture, speed, 0);
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_LEFT)) mint_PhysApplyForce(texture, -speed, 0);
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_UP)) mint_PhysApplyForce(texture, 0, -speed);
		if (mint_InputCheckKey(sys->input, SDL_SCANCODE_DOWN)) mint_PhysApplyForce(texture, 0, speed);

		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		mint_TextureUpdate(texture, sys->timer->elapsed);
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

	mint_PhysEnable(box1, 1, 1);
	mint_PhysEnable(box2, 1, 1);

	MintFloatPoint velo1;
	MintFloatPoint velo2;

	mint_TextureSetColour(box1, &red);
	mint_TextureSetColour(box2, &blue);

	mint_PhysSetGravity(sys, 0, 5);

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		secondsTillRegen -= sys->timer->elapsed;
		if (secondsTillRegen <= 0) {
			secondsTillRegen = 1;

			if (rand() % 2) {
				mint_TextureSetX(box1, rand() % (sys->gameWidth - box1->width));
				mint_TextureSetY(box1, (rand() % 20) + 20);

				mint_TextureSetX(box2, rand() % (sys->gameWidth - box1->width));
				mint_TextureSetY(box2, sys->gameHeight - box1->height - (rand() % 20) - 20);
			} else {
				mint_TextureSetX(box1, 20);
				mint_TextureSetY(box1, rand() % (sys->gameHeight - box1->height));

				mint_TextureSetX(box2, sys->gameWidth - box1->width - (rand() % 20) - 20);
				mint_TextureSetY(box2, rand() % (sys->gameHeight - box1->height));
			}

			velo1.x = (float)(box2->x - box1->x);
			velo1.y = (float)(box2->y - box1->y);
			velo2.x = (float)(box1->x - box2->x);
			velo2.y = (float)(box1->y - box2->y);

			mint_GeomNormalizeFloatPoint(&velo1, 10);
			mint_GeomNormalizeFloatPoint(&velo2, 10);

			mint_PhysSetVelocity(box1, velo1.x, velo1.y);
			mint_PhysSetVelocity(box2, velo2.x, velo2.y);
		}

		mint_SystemUpdate(sys);

		mint_TextureUpdate(box1, sys->timer->elapsed);
		mint_TextureUpdate(box2, sys->timer->elapsed);

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
		mint_AnimCreateFromXML(player[i], "assets/img/player_blue.xml");
		
		mint_AnimPlay(mint_AnimGetByIndex(player[i], i));
		mint_AnimGetByIndex(player[i], i)->loop = 1;

		mint_TextureSetX(player[i], 50 * i);
	}

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		for (i = 0; i < ANIMS; i++) mint_TextureUpdate(player[i], sys->timer->elapsed);

		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		for (i = 0; i < ANIMS; i++) mint_TextureRender(player[i]);

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}
	
	for (i = 0; i < ANIMS; i++) mint_TextureFree(player[i]);
}

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
	mint_TextureResizeHit(player, 52, 66);
	mint_PhysEnable(player, 1, 1);
	mint_PhysSetGravity(sys, 0, 0);
	mint_PhysSetDamping(player, 50);
	
	mint_AnimCreateFromXML(player, "assets/img/player_blue.xml");
	for (i = 0; i < player->totalAnims; i++) mint_AnimGetByIndex(player, i)->loop = 1;

	mint_AnimPlay(mint_AnimGetByName(player, "player_blue_SMG_downRight_running_"));

	mint_TextureSetX(player, 200);
	mint_TextureSetY(player, 200);

	for(;;)
	{
		mint_SystemPreUpdate(sys);

		left = mint_InputCheckKey(sys->input, SDL_SCANCODE_LEFT);
		right = mint_InputCheckKey(sys->input, SDL_SCANCODE_RIGHT);
		up = mint_InputCheckKey(sys->input, SDL_SCANCODE_UP);
		down = mint_InputCheckKey(sys->input, SDL_SCANCODE_DOWN);

		if (left) mint_PhysSetVelocity(player, -5, mint_PhysGetVelocity(player).y);
		if (right) mint_PhysSetVelocity(player, 5, mint_PhysGetVelocity(player).y);
		if (up) mint_PhysSetVelocity(player, mint_PhysGetVelocity(player).x, -5);
		if (down) mint_PhysSetVelocity(player, mint_PhysGetVelocity(player).x, 5);

		strcpy(animStr, "player_blue_SMG_");

		if (up && right) {
			strcat(animStr, "upRight");
			player->flip = SDL_FLIP_NONE;
		} else if (down && right) {
			strcat(animStr, "downRight");
			player->flip = SDL_FLIP_NONE;
		} else if (up && left) {
			strcat(animStr, "upRight");
			player->flip = SDL_FLIP_HORIZONTAL;
		} else if (down && left) {
			strcat(animStr, "downRight");
			player->flip = SDL_FLIP_HORIZONTAL;
		} else if (left) {
			strcat(animStr, "right");
			player->flip = SDL_FLIP_HORIZONTAL;
			dirStr = GEOM_LEFT;
		} else if (right) {
			strcat(animStr, "right");
			player->flip = SDL_FLIP_NONE;
			dirStr = GEOM_RIGHT;
		} else if (up) {
			strcat(animStr, "up");
			player->flip = SDL_FLIP_NONE;
			dirStr = GEOM_UP;
		} else if (down) {
			strcat(animStr, "down");
			player->flip = SDL_FLIP_NONE;
			dirStr = GEOM_DOWN;
		} else {
			if (dirStr == GEOM_LEFT) {
				strcat(animStr, "right");
				player->flip = SDL_FLIP_HORIZONTAL;
			} else {
				player->flip = SDL_FLIP_NONE;
			}

			if (dirStr == GEOM_RIGHT) strcat(animStr, "right");
			if (dirStr == GEOM_UP) strcat(animStr, "up");
			if (dirStr == GEOM_DOWN) strcat(animStr, "down");
		}

		strcat(animStr, up || down || left || right ? "_running_" : "_standing_");

		mint_AnimPlay(mint_AnimGetByName(player, animStr));

		mint_TextureUpdate(player, sys->timer->elapsed);

		mint_SystemUpdate(sys);
		mint_SystemPostUpdate(sys);
		mint_SystemPreDraw(sys);

		mint_TextureRender(player);

		mint_SystemDraw(sys);
		mint_SystemPostDraw(sys);
	}

	mint_TextureFree(player);
}

void tilemapExample(MintSystem* sys)
{	
	mint_TilemapCreate(sys, "assets/img/tilemap.png", 64, 64, 0);
	mint_SystemFullScreen(sys, 1);

	mint_TilemapGenerateFromTiled(sys->tilemap, "assets/map/test1.tmx");

	for(;;)
	{
		mint_SystemUpdate(sys);
		mint_SystemDraw(sys);
	}
}

void systemExample(MintSystem* sys)
{
	// mint_SystemFullScreen(sys, 1);

	mint_TilemapCreate(sys, "assets/img/tilemap.png", 64, 64, 0);
	mint_TilemapGenerateFromTiled(sys->tilemap, "assets/map/test1.tmx");

	// MintTexture* texture = mint_TextureFromPNG(sys, "assets/img/pngSplash.png");
	// mint_SystemAddTexture(sys, texture);

	for(;;)
	{
		mint_SystemUpdate(sys);
		mint_SystemDraw(sys);
	}
}