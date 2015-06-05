#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

struct InputSetup {
	char status[281];
};

InputSetup *mint_InputSetup();
void mint_InputUpdate(InputSetup *input, SDL_KeyboardEvent *key);
char mint_InputCheckStatus(InputSetup *input, int keycode);

#endif