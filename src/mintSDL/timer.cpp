#include <stdio.h>
#include <SDL.h>
#include "timer.h"

MintFrameTimer* mint_TimerSetup()
{
	MintFrameTimer* timer = (MintFrameTimer*)calloc(1, sizeof(MintFrameTimer));
	return timer;
}

void mint_TimerUpdate(MintFrameTimer* timer, int ticks)
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

void mint_TimerFree(MintFrameTimer* timer)
{
	free(timer);
	timer = NULL;
}