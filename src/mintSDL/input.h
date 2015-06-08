#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

struct MintInput {
	char status[281];
};

MintInput* mint_InputSetup();
void mint_InputUpdate(MintInput* input, SDL_KeyboardEvent* key);
char mint_InputCheckStatus(MintInput* input, int keycode);
void mint_InputFree(MintInput* input);

#endif