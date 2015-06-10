#ifndef TIMER_H
#define TIMER_H

struct MintFrameTimer {
	int ticks;
	int frames;
	int elapsed;
	float msPerReport;
	float msSinceLastReport;
};

MintFrameTimer* mint_TimerSetup();
void mint_TimerUpdate(MintFrameTimer* timer, int ticks);
void mint_TimerFree(MintFrameTimer* timer);

#endif