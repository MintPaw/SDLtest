#ifndef ANIM_H
#define ANIM_H

struct MintAnim;
struct MintAnimMan;

#include <SDL.h>
#include "texture.h"
#include "mintSDL/input.h"

struct MintAnimMan {
	MintTexture* mintTexture;
	MintAnim* anims;
	MintAnim* currentAnim;
	int totalAnims;
};

struct MintAnim {
	char* name;
	char loop;
	int totalFrames;
	int currentFrame;
	SDL_Rect* frameRects;
	MintAnimMan* man;
};

MintAnimMan* mint_AnimManSetup(MintTexture* mintTexture);
void mint_AnimCreate(MintAnimMan* animMan, int index, char* name, int totalFrames);
void mint_AnimDefineFrame(MintAnim* anim, int frameNumber, int x, int y, int width, int height);
void mint_AnimDefineFrames(MintAnim* anim, SDL_Rect* frameRects);
void mint_AnimDefineLinearStripFrames(MintAnim* anim, int frameWidth, char loop);
void mint_AnimUpdate(MintAnimMan* animMan);
void mint_AnimUpdateAsButton(MintAnimMan* animMan, MintInput* input);
MintAnim* mint_AnimGetByIndex(MintAnimMan* animMan, int index);
void mint_AnimPlay(MintAnim* anim);
void mint_AnimNextFrame(MintAnimMan* animMan);
void mint_AnimGotoFrame(MintAnimMan* animMan, int index);
void mint_AnimManFree(MintAnimMan* animMan);
void mint_AnimManInit(MintAnimMan* animMan, int totalAnims);

#endif