#ifndef TIMER_H
#define TIMER_H

struct MintFrameTimer;

struct MintFrameTimer {
	float seconds;
	int frames;
	int ticks;
	float elapsed;
	float secondsPerReport;
	float secondsSinceLastReport;
	float fpsAverage;
};

MintFrameTimer* mint_TimerSetup();
void mint_TimerUpdate(MintFrameTimer* timer, float seconds);
void mint_TimerFree(MintFrameTimer* timer);

#endif