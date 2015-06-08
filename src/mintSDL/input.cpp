#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "input.h"

MintInput* mint_InputSetup()
{
	MintInput* input = (MintInput*)calloc(1, sizeof(MintInput));

	return input;
}

void mint_InputUpdate(MintInput* input, SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
		input->keyStatus[event->key.keysym.scancode] = event->key.state == SDL_PRESSED;
	} else if (event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEBUTTONDOWN) {
		if (event->button.button == SDL_BUTTON_LEFT) {
			input->mouseButtonStatus[0] = event->button.state == SDL_PRESSED;
		} else if (event->button.button == SDL_BUTTON_RIGHT) {
			input->mouseButtonStatus[1] = event->button.state == SDL_PRESSED;
		} else if (event->button.button == SDL_BUTTON_MIDDLE) {
			input->mouseButtonStatus[2] = event->button.state == SDL_PRESSED;
		}
	} else if (event->type == SDL_MOUSEMOTION) {
		input->mousePoint.x = event->motion.x;
		input->mousePoint.y = event->motion.y;
	}
}

char mint_InputCheckStatus(MintInput* input, int keycode)
{
	return input->keyStatus[keycode];
}

void mint_InputFree(MintInput* input)
{
	free(input);
	input = NULL;
}