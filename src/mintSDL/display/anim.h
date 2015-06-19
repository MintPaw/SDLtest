#ifndef ANIM_H
#define ANIM_H

struct MintAnim;

#include <SDL.h>
#include "texture.h"
#include "mintSDL/util/input.h"

struct MintAnim {
	MintTexture* mintTexture;
	char* name;
	char loop;
	int totalFrames;
	int currentFrame;
	int frameRate;
	SDL_Rect* frameRects;
	float _timeTillNextFrame;
};

void mint_AnimCreate(MintTexture* mintTexture, int index, char* name, int totalFrames, int frameRate);
void mint_AnimDefineFrame(MintAnim* anim, int frameNumber, int x, int y, int width, int height);
void mint_AnimDefineFrames(MintAnim* anim, SDL_Rect* frameRects);
void mint_AnimDefineLinearStripFrames(MintAnim* anim, int frameWidth, char loop);
void mint_AnimUpdate(MintTexture* mintTexture, float elapsed);
void mint_AnimUpdateClip(MintTexture* mintTexture);
void mint_AnimUpdateAsButton(MintTexture* mintTexture, MintInput* input);
MintAnim* mint_AnimGetByIndex(MintTexture* mintTexture, int index);
MintAnim* mint_AnimGetByName(MintTexture* mintTexture, char* name);
void mint_AnimPlay(MintAnim* anim);
void mint_AnimNextFrame(MintTexture* mintTexture);
void mint_AnimGotoFrame(MintTexture* mintTexture, int index);
void mint_AnimInit(MintTexture* mintTexture, int totalAnims);
void mint_AnimCreateFromXML(MintTexture* mintTexture, char* xmlPath);
void mint_AnimFree(MintTexture* mintTexture);

#endif