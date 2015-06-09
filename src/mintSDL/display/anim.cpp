#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "anim.h"
#include "texture.h"
#include "trans.h"
#include "..\maths.h"

void mint_AnimCreate(MintAnimMan* animMan, int index, char* name, int totalFrames)
{
	MintAnim* anim = mint_AnimGetByIndex(animMan, index);

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
		mint_AnimDefineFrame(anim, i, frameWidth * i, 0, frameWidth, mint_TransGetHeight(anim->man->mintTexture->trans));
	}

	anim->currentFrame = 0;
	anim->loop = loop;

	anim->man->mintTexture->rend->_clipRect = &anim->frameRects[0];
	anim->man->mintTexture->trans->_width = anim->frameRects[0].w;
	anim->man->mintTexture->trans->_height = anim->frameRects[0].h;
}

void mint_AnimUpdate(MintAnimMan* animMan)
{
	animMan->mintTexture->rend->_clipRect = &animMan->currentAnim->frameRects[animMan->currentAnim->currentFrame];	
}

void mint_AnimUpdateAsButton(MintAnimMan* animMan, MintInput* input)
{
	SDL_Rect rect = { animMan->mintTexture->trans->x, animMan->mintTexture->trans->y, animMan->mintTexture->trans->_width, animMan->mintTexture->trans->_height };
	if (mint_MathsPointInRect(&input->mousePoint, &rect)) {
		if (input->mouseButtonStatus[0]) {
			mint_AnimGotoFrame(animMan, 2);
		} else {
			mint_AnimGotoFrame(animMan, 1);
		}
	} else {
		mint_AnimGotoFrame(animMan, 0);
	}
}

MintAnim* mint_AnimGetByIndex(MintAnimMan* animMan, int index)
{
	return &animMan->anims[index];
}

void mint_AnimPlay(MintAnim* anim)
{
	anim->man->currentAnim = anim;
}

void mint_AnimNextFrame(MintAnimMan* animMan)
{
	if (animMan->currentAnim->currentFrame < animMan->currentAnim->totalFrames - 1) {
		animMan->currentAnim->currentFrame++;
	} else if (animMan->currentAnim->loop) {
		animMan->currentAnim->currentFrame = 0;
	}
	
	mint_AnimUpdate(animMan);
}

void mint_AnimGotoFrame(MintAnimMan* animMan, int index)
{
	animMan->currentAnim->currentFrame = index;
	mint_AnimUpdate(animMan);
}

void mint_AnimManFree(MintAnimMan* animMan)
{
	int i;
	for (i = 0; i < animMan->totalAnims; i++) {
		free(animMan->anims[i].frameRects);
	}

	free(animMan);
	animMan = NULL;
}