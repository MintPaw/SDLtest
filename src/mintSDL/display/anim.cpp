#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "anim.h"
#include "texture.h"
#include "trans.h"

void mint_AnimSetup(MintAnim* anim, char* name, int totalFrames)
{
	anim->name = name;
	anim->frameRects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * totalFrames);
	anim->totalFrames = totalFrames;
	anim->totalFrames = totalFrames;
}

void mint_AnimDefineFrame(MintAnim* anim, int frameNumber, int x, int y, int width, int height)
{
	anim->frameRects[frameNumber] = {x, y, width, height};
}

void mint_AnimDefineFrames(MintAnim* anim, SDL_Rect* frameRects)
{
	anim->frameRects = frameRects;
}

void mint_AnimDefineLinearStripFrames(MintAnim* anim, int frameWidth, char loop)
{
	int i;
	for (i = 0; i < anim->totalFrames; i++) {
		mint_AnimDefineFrame(anim, i, frameWidth * i, 0, frameWidth, mint_TransGetHeight(anim->man->texture->trans));
	}

	anim->currentFrame = 0;
	anim->loop = loop;

	anim->man->texture->_clipRect = &anim->frameRects[0];
}

void mint_AnimNextFrame(MintAnimMan* animMan)
{
	if (animMan->currentAnim->currentFrame < animMan->currentAnim->totalFrames - 1) {
		animMan->currentAnim->currentFrame++;
	} else if (animMan->currentAnim->loop) {
		animMan->currentAnim->currentFrame = 0;
	}

	// printf("Frame %d of %d\n", animMan->currentAnim->currentFrame, animMan->currentAnim->totalFrames);
	
	mint_AnimUpdate(animMan);
}

void mint_AnimUpdate(MintAnimMan* animMan)
{
	animMan->texture->_clipRect = &animMan->currentAnim->frameRects[animMan->currentAnim->currentFrame];	
	// printf("Clip rect: x: %d, y: %d, w: %d, h: %d\n", animMan->texture->_clipRect->x, animMan->texture->_clipRect->y, animMan->texture->_clipRect->w, animMan->texture->_clipRect->h);
}

void mint_AnimPlayByIndex(MintAnimMan* animMan, int index)
{
	animMan->currentAnim = &animMan->anims[index];
}