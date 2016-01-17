#ifndef TIMERS_H
#define TIMERS_H

#include <vector>
#include <sys/time.h>
#include <errno.h> 
#include <sys/signal.h>

class Timers
{
	private:
		int nmbTimers;							// Number of timers
		std::vector<unsigned short> timer;		// vector for storing timers
		static int updateTime;

	public:
		Timers(int max);						// default constructor
		void config(void);
		void incTime(void);						// increment timers
		static void timer_handler(int s);		//
		unsigned short getTimer(int tnmb);		// get ms timer
};

#endif