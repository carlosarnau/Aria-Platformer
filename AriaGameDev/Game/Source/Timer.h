#pragma once
#ifndef __TIMER_H__
#define __TIMER_H__

#include "Defs.h"


class Timer
{
public:
	// Constructor
	Timer();
	~Timer() {};

	void Start();
	uint Read() const;
	float ReadSec() const;
	float ReadSecSince(float plus) const;

private:
	uint	started_at;
};

#endif 