#include <stdlib.h>
#include "input.h"

InputSetup *setup()
{
	InputSetup *input = (InputSetup *)calloc(1, sizeof(InputSetup));

	return input;
}