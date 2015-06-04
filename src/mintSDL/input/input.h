#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

struct InputSetup {
	char status[281];
};

InputSetup *setupInput();
void updateInput(InputSetup *input, SDL_Key *key);

#endif