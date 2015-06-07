#ifndef ANIM_H
#define ANIM_H

struct MintAnim;

#include <SDL.h>
#include "texture.h"

struct MintAnim {
	char* name;
	int totalFrames;
	char loop;
	int currentFrame;
	SDL_Rect* frameRects;
	MintTexture* texture;
};

void mint_AnimSetup(MintAnim* anim, char* name, int totalFrames);
void mint_AnimDefineFrame(MintAnim* anim, int frameNumber, int x, int y, int width, int height);
void mint_AnimDefineFrames(MintAnim* anim, SDL_Rect* frameRects);
void mint_AnimDefineLinearStripFrames(MintAnim* anim, int frameWidth, char loop);
void mint_AnimNextFrame(MintAnim* anim);
void mint_AnimUpdateAnim(MintAnim* anim);

#endif