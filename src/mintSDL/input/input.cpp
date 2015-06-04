#include <stdlib.h>
#include <SDL.h>
#include "input.h"

InputSetup *setupInput()
{
	InputSetup *input = (InputSetup *)calloc(1, sizeof(InputSetup));

	return input;
}

void updateInput(InputSetup *input, SDL_Key *key) {

}