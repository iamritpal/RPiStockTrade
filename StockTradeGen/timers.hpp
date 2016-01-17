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
		std::vector<unsigned short> timer10ms;		// vector for storing timers
		std::vector<unsigned short> timer100ms;		// vector for storing timers
		int counter10ms;
		static int updateTime;

	public:
		Timers(int max);						// default constructor
		void config(void);
		void incTime(void);						// increment timers
		static void timer_handler(int s);			//
		void clr10msTimer(int tnmb);
		void clr100msTimer(int tnmb);
		unsigned short get10msTimer(int tnmb);		// get ms timer
		unsigned short get100msTimer(int tnmb);		// get ms timer
};

#endif