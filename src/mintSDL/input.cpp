#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "input.h"

InputSetup* mint_InputSetup()
{
	InputSetup* input = (InputSetup* )calloc(1, sizeof(InputSetup));

	return input;
}

void mint_InputUpdate(InputSetup* input, SDL_KeyboardEvent* key)
{
	input->status[key->keysym.scancode] = key->state == SDL_PRESSED;
}

char mint_InputCheckStatus(InputSetup* input, int keycode)
{
	return input->status[keycode];
}