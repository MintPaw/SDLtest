#ifndef TIMER_H
#define TIMER_H

struct MintTimer {
	char isStarted;
	char isPaused;
	int ticks;
	int frames;
	float elapsed;
	float msPerReport;
	float msSinceLastReport;
};

MintTimer* mint_TimerSetup();
void mint_TimerUpdate(MintTimer* timer, int ticks);

#endif