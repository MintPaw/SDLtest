#ifndef TIMER_H
#define TIMER_H

struct MintFrameTimer {
	double seconds;
	int frames;
	double elapsed;
	float msPerReport;
	float msSinceLastReport;
};

MintFrameTimer* mint_TimerSetup();
void mint_TimerUpdate(MintFrameTimer* timer, double seconds);
void mint_TimerFree(MintFrameTimer* timer);

#endif