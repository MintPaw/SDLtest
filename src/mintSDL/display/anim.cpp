#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL.h>
#include "mintSDL/display/anim.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/display/trans.h"
#include "mintSDL/maths/geom.h"

MintAnimMan* mint_AnimManSetup(MintTexture* mintTexture)
{
	MintAnimMan* animMan = (MintAnimMan*)malloc(sizeof(MintAnimMan));

	animMan->totalAnims = 0;
	animMan->currentAnim = NULL;
	animMan->mintTexture = mintTexture;

	return animMan;
}

void mint_AnimManInit(MintAnimMan* animMan, int totalAnims)
{
	animMan->anims = (MintAnim*)malloc(sizeof(MintAnim) * totalAnims);
	animMan->totalAnims = totalAnims;

	int i;
	for (i = 0; i < totalAnims; i++) animMan->anims[i].man = animMan;
}

void mint_AnimParseFromXML(MintAnimMan* animMan, char* xmlPath)
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
			// printf("Name %s", tokens[1]);
			for (i = strlen(tokens[1]); ; i--) {
				if (tokens[1][i] == '_') {
					tokens[1][i+1] = '\0';
					break;
				}
			}
			// printf(" resolved to %s\n", tokens[1]);

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
	char* currentName = (char*)malloc(sizeof(char*)*99);

	strcpy(currentName, names[0]);
	totalAnims = 1;

	for (i = 0; i < frameCount; i++) {
		if (strcmp(currentName, names[i])) {
			totalAnims++;
			strcpy(currentName, names[i]);
		}
	}

	mint_AnimManInit(animMan, totalAnims);

	int startFrame = 0;
	int endFrame = 0;
	int currentAnim = 0;

	strcpy(currentName, names[0]);

	// NOTE(jeru): Make sure everything ends with _XXXX.png
	for (i = 0; i < frameCount; i++) {
		if (strcmp(currentName, names[i])) {
			endFrame = i;
			mint_AnimCreate(animMan, currentAnim, currentName, endFrame - startFrame, 60);
			for (j = startFrame; j < endFrame; j++) {
				mint_AnimDefineFrame(mint_AnimGetByIndex(animMan, currentAnim),
			                       j - startFrame,
			                       rects[j].x,
			                       rects[j].y,
			                       rects[j].w,
			                       rects[j].h);
			}
			startFrame = endFrame;
			currentAnim++;
			strcpy(currentName, names[i]);
		}
	}

	free(currentName);
}

void mint_AnimCreate(MintAnimMan* animMan, int index, char* name, int totalFrames, int frameRate)
{
	MintAnim* anim = mint_AnimGetByIndex(animMan, index);

	anim->name = (char*)malloc(sizeof(char)*strlen(name));
	strcpy(anim->name, name);

	anim->frameRects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * totalFrames);
	anim->totalFrames = totalFrames;
	anim->frameRate = frameRate;
	anim->loop = 0;
	anim->currentFrame = 0;
	anim->_timeTillNextFrame = 1.0 / frameRate;
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

void mint_AnimUpdate(MintAnimMan* animMan, float elapsed)
{
	MintAnim* anim = animMan->currentAnim;
	
	anim->_timeTillNextFrame -= elapsed;
	if (anim->_timeTillNextFrame <= 0) {
		anim->_timeTillNextFrame = 1.0 / anim->frameRate;
		mint_AnimNextFrame(animMan);
	}
}

void mint_AnimUpdateClip(MintAnimMan* animMan)
{
	animMan->mintTexture->rend->_clipRect = &animMan->currentAnim->frameRects[animMan->currentAnim->currentFrame];	
}

void mint_AnimUpdateAsButton(MintAnimMan* animMan, MintInput* input)
{
	SDL_Rect rect = { animMan->mintTexture->trans->_x, animMan->mintTexture->trans->_y, animMan->mintTexture->trans->_width, animMan->mintTexture->trans->_height };
	if (mint_GeomPointInRect(&input->mousePoint, &rect)) {
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

MintAnim* mint_AnimGetByName(MintAnimMan* animMan, char* name)
{
	int i;
	for (i = 0; i < animMan->totalAnims; i++) {
		if (!strcmp(animMan->anims[i].name, name)) return &animMan->anims[i];
	}

	return NULL;
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
	
	mint_AnimUpdateClip(animMan);
}

void mint_AnimGotoFrame(MintAnimMan* animMan, int index)
{
	animMan->currentAnim->currentFrame = index;
	mint_AnimUpdateClip(animMan);
}

void mint_AnimManFree(MintAnimMan* animMan)
{
	int i;
	for (i = 0; i < animMan->totalAnims; i++) {
		free(animMan->anims[i].frameRects);
		animMan->anims[i].frameRects = NULL;
		// TODO(jeru): Free names?
		
		free(animMan->anims);
		animMan->anims = NULL;
	}

	free(animMan);
	animMan = NULL;
}