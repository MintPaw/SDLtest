#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL.h>
#include "mintSDL/display/anim.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/maths/geom.h"

void mint_AnimInit(MintTexture* mintTexture, int totalAnims)
{
	mintTexture->anims = (MintAnim*)malloc(sizeof(MintAnim) * totalAnims);
	mintTexture->totalAnims = totalAnims;

	int i;
	for (i = 0; i < totalAnims; i++) mintTexture->anims[i].mintTexture = mintTexture;
}

void mint_AnimCreateFromXML(MintTexture* mintTexture, char* xmlPath)
{
	FILE* fp;
	char buf[1024];
	int i;
	int j;

	// TODO(jeru): Note this limitation
	SDL_Rect rects[999];
	char names[999][99];
	int frameCount = 0;
	char* token;
	char tokens[11][99];
	char currentToken = 0;

	if ((fp = fopen(xmlPath, "r")) == NULL) {
		printf("Failed to load xml");
		return;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL) {
		buf[strlen(buf) - 1] = '\0';

		if (buf[0] == ' ' && buf[4] == '<') {
			currentToken = 0;
			token = strtok(buf, "\"");

			while (token != NULL) {
				strcpy(tokens[currentToken], token);
				currentToken++;
				token = strtok(NULL, "\"");
			}

			for (i = strlen(tokens[1]); ; i--) {
				if (tokens[1][i] == '_') {
					tokens[1][i+1] = '\0';
					break;
				}
			}

			strcpy(names[frameCount], tokens[1]);
			rects[frameCount].x = atoi(tokens[3]);
			rects[frameCount].y = atoi(tokens[5]);
			rects[frameCount].w = atoi(tokens[7]);
			rects[frameCount].h = atoi(tokens[9]);
			frameCount++;
		}
	}

	fclose(fp);

	int totalAnims = 0;
	char* currentName;

	currentName = names[0];

	for (i = 0; i < frameCount; i++) {
		if (strcmp(currentName, names[i])) {
			totalAnims++;
			currentName = names[i];
		}
	}

	mint_AnimInit(mintTexture, totalAnims);

	int startFrame = 0;
	int endFrame = 0;
	int currentAnim = 0;

	strcpy(currentName, names[0]);

	// NOTE(jeru): Make sure everything ends with _XXXX.png
	for (i = 0; i < frameCount; i++) {
		if (strcmp(currentName, names[i])) {
			endFrame = i;
			mint_AnimCreate(mintTexture, currentAnim, currentName, endFrame - startFrame, 60);
			for (j = startFrame; j < endFrame; j++) {
				mint_AnimDefineFrame(mint_AnimGetByIndex(mintTexture, currentAnim),
			                       j - startFrame,
			                       rects[j].x,
			                       rects[j].y,
			                       rects[j].w,
			                       rects[j].h);
			}
			startFrame = endFrame;
			currentAnim++;
			currentName = names[i];
		}
	}
}

void mint_AnimCreate(MintTexture* mintTexture, int index, char* name, int totalFrames, int frameRate)
{
	MintAnim* anim = mint_AnimGetByIndex(mintTexture, index);

	anim->name = (char*)malloc(sizeof(char)*(strlen(name) + 1));
	strcpy(anim->name, name);

	anim->frameRects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * totalFrames);
	anim->totalFrames = totalFrames;
	anim->frameRate = frameRate;
	anim->loop = 0;
	anim->currentFrame = 0;
	anim->_timeTillNextFrame = (float)(1.0 / frameRate);
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
		mint_AnimDefineFrame(anim, i, frameWidth * i, 0, frameWidth, anim->mintTexture->height);
	}

	anim->currentFrame = 0;
	anim->loop = loop;

	anim->mintTexture->clipRect = &anim->frameRects[0];
	anim->mintTexture->width = anim->frameRects[0].w;
	anim->mintTexture->height = anim->frameRects[0].h;
}

void mint_AnimUpdate(MintTexture* mintTexture, float elapsed)
{
	if (!mintTexture->currentAnim) return;
	MintAnim* anim = mintTexture->currentAnim;
	
	anim->_timeTillNextFrame -= elapsed;
	if (anim->_timeTillNextFrame <= 0) {
		anim->_timeTillNextFrame = (float)(1.0 / anim->frameRate);
		mint_AnimNextFrame(mintTexture);
	}
}

void mint_AnimUpdateClip(MintTexture* mintTexture)
{
	mintTexture->clipRect = &mintTexture->currentAnim->frameRects[mintTexture->currentAnim->currentFrame];	
}

void mint_AnimUpdateAsButton(MintTexture* mintTexture, MintInput* input)
{
	SDL_Rect rect = { mintTexture->x, mintTexture->y, mintTexture->width, mintTexture->height };
	if (mint_GeomPointInRect(&input->mousePoint, &rect)) {
		if (input->mouseButtonStatus[0]) {
			mint_AnimGotoFrame(mintTexture, 2);
		} else {
			mint_AnimGotoFrame(mintTexture, 1);
		}
	} else {
		mint_AnimGotoFrame(mintTexture, 0);
	}
}

MintAnim* mint_AnimGetByIndex(MintTexture* mintTexture, int index)
{
	return &mintTexture->anims[index];
}

MintAnim* mint_AnimGetByName(MintTexture* mintTexture, char* name)
{
	int i;
	for (i = 0; i < mintTexture->totalAnims; i++) {
		if (!strcmp(mintTexture->anims[i].name, name)) return &mintTexture->anims[i];
	}

	return NULL;
}

void mint_AnimPlay(MintAnim* anim)
{
	anim->mintTexture->currentAnim = anim;
}

void mint_AnimNextFrame(MintTexture* mintTexture)
{
	if (mintTexture->currentAnim->currentFrame < mintTexture->currentAnim->totalFrames - 1) {
		mintTexture->currentAnim->currentFrame++;
	} else if (mintTexture->currentAnim->loop) {
		mintTexture->currentAnim->currentFrame = 0;
	}
	
	mint_AnimUpdateClip(mintTexture);
}

void mint_AnimGotoFrame(MintTexture* mintTexture, int index)
{
	mintTexture->currentAnim->currentFrame = index;
	mint_AnimUpdateClip(mintTexture);
}

void mint_AnimFree(MintTexture* mintTexture)
{
	int i;
	for (i = 0; i < mintTexture->totalAnims; i++) {
		free(mintTexture->anims[i].frameRects);
		free(mintTexture->anims[i].name);
		mintTexture->anims[i].name = NULL;
		mintTexture->anims[i].frameRects = NULL;	
	}

	if (mintTexture->anims) {
		free(mintTexture->anims);
		mintTexture->anims = NULL;
	}
}