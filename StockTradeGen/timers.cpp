#include <iostream>
#include "timers.hpp"

int Timers::updateTime = 0;

// Timers constructor

Timers::Timers(int max)
{
	updateTime = 0;
	nmbTimers = max;
	timer.resize(max);		// resize vector
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

	std::cout << "\n%d sec up partner, Wakeup!!!\n" << std::endl;
	tout_val.it_value.tv_sec = 0; 
	tout_val.it_value.tv_usec = 10000;	/* 10 useconds timer */
	tout_val.it_interval.tv_sec = 0;
	tout_val.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &tout_val,0);
	signal(SIGALRM,&Timers::timer_handler);
}

// Increment timers

void Timers::incTime(void)
{
	int i=0;
	while (i < nmbTimers)
	{
		timer[i]++;
		i++;		
	}

}

// Get timer value

unsigned short Timers::getTimer(int tnmb)
{
	return timer[tnmb];
}