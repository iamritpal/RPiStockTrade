#ifndef TIMERS_H
#define TIMERS_H

#include <vector>
#include <sys/time.h>
#include <errno.h> 
#include <sys/signal.h>

class Timers
{
	private:
		int nmbTimers;								// Number of timers
		int counter10ms;
		std::vector<unsigned short> timer10ms;		// vector for storing timers
		std::vector<unsigned short> timer100ms;		// vector for storing timers
		static int updateTime;
		static Timers* m_pInstance;


	public:
		Timers(int max);							// default constructor
		void config(void);
		void incTime(void);							// increment timers
		void clr10msTimer(int tnmb);
		void clr100msTimer(int tnmb);
		unsigned short get10msTimer(int tnmb);		// get ms timer
		unsigned short get100msTimer(int tnmb);		// get ms timer
		
		static Timers* Instance(int max);
		static void timer_handler(int s);			//
};

#endif