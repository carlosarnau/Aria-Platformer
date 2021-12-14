#pragma once
#ifndef __PERFTIMER_H__
#define __PERFTIMER_H__

#include "Defs.h"

class PerfTimer
{
public:

	
	PerfTimer();
	~PerfTimer() {};

	void Start();
	double ReadMs() const;
	uint ReadTicks() const;

private:
	uint	started_at;
	static uint frequency;
};

#endif 