/*
Copyright (c) 2022 Generation Loss Interactive

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __ROUNDERING_TIMER_H__
#define __ROUNDERING_TIMER_H__

#include "pd_api.h"

typedef struct pdTimer
{
	bool running;
	float start;
	float total;
	int count;
} pdTimer;

static inline void pdTimer_initialize(pdTimer *timer)
{
	timer->running = false;
	timer->start = 0;
	timer->total = 0;
	timer->count = 0;
}

static inline void pdTimer_start(pdTimer *timer, PlaydateAPI* pd)
{
	timer->running = true;
	timer->start = pd->system->getElapsedTime();
}

static inline void pdTimer_end(pdTimer *timer, const char* name, PlaydateAPI* pd)
{
	timer->total += pd->system->getElapsedTime() - timer->start;
	timer->count++;
	timer->running = false;
	pd->system->logToConsole("PDTimer %s: %0.3f milliseconds", name, (timer->total / timer->count) * 1000.0f);
}

#endif /* __ROUNDERING_TIMER_H__ */



