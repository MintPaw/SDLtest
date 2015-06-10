#include <stdio.h>
#include <SDL.h>
#include "timer.h"

MintFrameTimer* mint_TimerSetup()
{
	MintFrameTimer* timer = (MintFrameTimer*)calloc(1, sizeof(MintFrameTimer));
	return timer;
}

void mint_TimerUpdate(MintFrameTimer* timer, double seconds)
{
	timer->elapsed = seconds - timer->seconds;
	timer->seconds = seconds;
	timer->frames++;

	if (timer->secondsSinceLastReport > 0) {
		timer->secondsSinceLastReport -= timer->elapsed;
		if (timer->secondsSinceLastReport <= 0) {
			printf("Average frame rate: %f\n", timer->frames / timer->seconds);
			timer->secondsSinceLastReport = timer->secondsPerReport;
		}
	}
}

void mint_TimerFree(MintFrameTimer* timer)
{
	free(timer);
	timer = NULL;
}