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
		anim->frameRects[i].x = frameWidth * i;
		anim->frameRects[i].y = 0;
		anim->frameRects[i].w = frameWidth;
		anim->frameRects[i].h = mint_TransGetHeight(anim->texture->trans);
	}

	anim->currentFrame = 0;
	anim->loop = loop;

	if (anim->texture->_clipRect != NULL) free(&anim->texture->_clipRect);
	anim->texture->_clipRect = &anim->frameRects[0];
}

void mint_AnimNextFrame(MintAnim* anim)
{
	if (anim->currentFrame < anim->totalFrames - 1) {
		anim->currentFrame++;
	} else if (anim->loop) {
		anim->currentFrame = 0;
	}
	
	mint_AnimUpdateAnim(anim);
}

void mint_AnimUpdateAnim(MintAnim* anim)
{
	anim->texture->_clipRect = &anim->frameRects[anim->currentFrame];	
}