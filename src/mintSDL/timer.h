#ifndef TIMER_H
#define TIMER_H

struct MintTimer {
	char isStarted;
	char isPaused;
	int ticks;
	int frames;
	int elapsed;
	float msPerReport;
	float msSinceLastReport;
};

MintTimer* mint_TimerSetup();
void mint_TimerUpdate(MintTimer* timer, int ticks);
void mint_TimerFree(MintTimer* timer);

#endif