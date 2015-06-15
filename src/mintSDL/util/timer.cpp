#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "mintSDL/util/timer.h"

MintFrameTimer* mint_TimerSetup()
{
	MintFrameTimer* timer = (MintFrameTimer*)malloc(sizeof(MintFrameTimer));
	timer->seconds = 0;
	timer->frames = 0;
	timer->ticks = 0;
	timer->elapsed = 0;
	timer->secondsPerReport = 0;
	timer->secondsSinceLastReport = -1;
	return timer;
}

void mint_TimerUpdate(MintFrameTimer* timer, float seconds)
{
	timer->ticks = seconds * 1000.0;
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