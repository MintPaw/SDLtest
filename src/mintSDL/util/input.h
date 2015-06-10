#ifndef INPUT_H
#define INPUT_H

struct MintInput;

#include <SDL.h>

struct MintInput {
	char keyStatus[281];
	char mouseButtonStatus[3];
	SDL_Point mousePoint;
};

MintInput* mint_InputSetup();
void mint_InputUpdate(MintInput* input, SDL_Event* event);
char mint_InputCheckStatus(MintInput* input, int keycode);
void mint_InputFree(MintInput* input);

#endif