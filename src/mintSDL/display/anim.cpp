#include <stdlib.h>
#include <SDL.h>
#include "anim.h"

MintAnim* mint_AnimCreate(char* name, int totalFrames)
{
	MintAnim* anim = (MintAnim*)malloc(sizeof(MintAnim));

	anim->frameRects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * totalFrames);
}

void mint_AnimDefineFrame(MintAnim* anim, int frameNumber, int x, int y, int width, int height)
{
	anim->frameRects[frameNumber] = {x, y, width, height};
}