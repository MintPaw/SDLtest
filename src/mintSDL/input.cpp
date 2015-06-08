#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "input.h"

MintInput* mint_InputSetup()
{
	MintInput* input = (MintInput*)calloc(1, sizeof(MintInput));

	return input;
}

void mint_InputUpdate(MintInput* input, SDL_KeyboardEvent* key)
{
	input->status[key->keysym.scancode] = key->state == SDL_PRESSED;
}

char mint_InputCheckStatus(MintInput* input, int keycode)
{
	return input->status[keycode];
}

void mint_InputFree(MintInput* input)
{
	free(input);
	input = NULL;
}