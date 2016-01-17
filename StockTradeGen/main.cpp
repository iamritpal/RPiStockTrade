//*****************************************
//	Software Engineer - Amritpal Singh
//	Date - 01-17-2016
//*****************************************

#include <iostream>
#include "timers.hpp"

// g++ -o main main.cpp timers.cpp

enum Timer { 
	tfirst,
	tsecond,
	tthird,
	nmbtmrs
};

Timers *timers = 0;

int main(void)
{
	int i=0;
	int count=0, sec=0;

	if (timers == 0)
		timers = timers->getInstance(nmbtmrs);

	timers->init();		// Initialize timers
	timers->config();	// Configure timers to work for 10ms and 100ms counters

	for(;;)
	{
		timers->incTime();		// Always check if timers need to be incremented

		count++;
		if (timers->get100msTimer(tfirst) >= 10)
		{
			std::cout << "sec = " << sec++ << " count = " << count << std::endl;
			count = 0;
			timers->clr100msTimer(tfirst);
		}
	}
	return 0;
}