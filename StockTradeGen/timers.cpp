//*****************************************
//	Software Engineer - Amritpal Singh
//	Date - 01-17-2016
//*****************************************

#include <iostream>
#include "timers.hpp"

int Timers::updateTime = 0;
Timers* Timers::m_pInstance = NULL;

// Timers constructor

Timers::Timers(int max)
{
	updateTime = 0;
	counter10ms = 0;
	nmbTimers = max;
	timer10ms.resize(max);		// resize vector
	timer100ms.resize(max);
}

Timers* Timers::getInstance(int max)
{
	if (!m_pInstance)   		// Only allow one instance of class to be generated.
		m_pInstance = new Timers(max);
	return m_pInstance;
}

void Timers::init(void)
{
	int i;

	for (i=0;i<nmbTimers;i++)
	{
		timer10ms[i] = 0;
		timer100ms[i] = 0;
	}
}

// Configure Timers

void Timers::config(void)
{
	struct itimerval itimer;
	/* Configure the timer to expire after 10 msec... */
	itimer.it_value.tv_sec = 0;
	itimer.it_value.tv_usec = 10000;
	/* ... and every 10 msec after that. */
	itimer.it_interval.tv_sec = 0;
	itimer.it_interval.tv_usec = 10000;

	/* Start a real timer. It counts down whenever this process is
	   executing. */
	if (setitimer(ITIMER_REAL, &itimer, 0) == -1)
		std::cout << "Error: cannot handle ITIMER_REAL" << std::endl;

	signal(SIGALRM,&Timers::timer_handler);
}

void Timers::timer_handler(int s)
{
	struct itimerval tout_val;
	
	updateTime = 1;

	// set for counter10ms 100 counts per second

	tout_val.it_value.tv_sec = 0; 
	tout_val.it_value.tv_usec = 10000;	/* 10000 for 10 milli timer */
	tout_val.it_interval.tv_sec = 0;
	tout_val.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &tout_val,0);
	signal(SIGALRM,&Timers::timer_handler);
}

// Increment timers

void Timers::incTime(void)
{
	int i=0;
	if (updateTime != 0)
	{
		updateTime = 0;
		counter10ms++;
		while (i < nmbTimers)
			timer10ms[i++]++;
		if (counter10ms >= 10)
		{
			i=0;
			while (i < nmbTimers)
				timer100ms[i++]++;
			counter10ms = 0;
		}
	}
}

// Get 10ms timer value

unsigned short Timers::get10msTimer(int tnmb)
{
	return timer10ms[tnmb];
}

// Get 100ms timer value

unsigned short Timers::get100msTimer(int tnmb)
{
	return timer100ms[tnmb];
}

void Timers::clr10msTimer(int tnmb)
{
	timer10ms[tnmb] = 0;
}

void Timers::clr100msTimer(int tnmb)
{
	timer100ms[tnmb] = 0;
}
