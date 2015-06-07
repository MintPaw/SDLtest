#include <stdlib.h>
#include <SDL.h>
#include "animation.h"

MintAnimation* mint_AnimationCreate(char* name, int totalFrames)
{
	MintAnimation* anim = (MintAnimation*)malloc(sizeof(MintAnimation));

	anim->frameRects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * totalFrames);
}

void mint_AnimationDefineFrame(MintAnimation* anim, int frameNumber, int x, int y, int width, int height)
{
	anim->frameRects[frameNumber] = {x, y, width, height};
}