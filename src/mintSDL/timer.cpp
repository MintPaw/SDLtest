#include <stdio.h>
#include <SDL.h>
#include "timer.h"

MintTimer* mint_TimerSetup()
{
	MintTimer* timer = (MintTimer*)calloc(1, sizeof(MintTimer));
	return timer;
}

void mint_TimerUpdate(MintTimer* timer, int ticks)
{
	timer->elapsed = ticks - timer->ticks;
	timer->ticks = ticks;
	timer->frames++;

	if (timer->msSinceLastReport > 0) {
		timer->msSinceLastReport -= timer->elapsed;
		if (timer->msSinceLastReport <= 0) {
			printf("Average frame rate: %f\n", (float)timer->frames / ((float)timer->ticks / 1000.0));
			timer->msSinceLastReport = timer->msPerReport;
		}
	}
}