//*****************************************
//	Software Engineer - Amritpal Singh
//	Date - 01-17-2016
//*****************************************

#include <iostream>
#include "timers.hpp"
#include "GPIOClass.hpp"

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

	GPIOClass* gpio4 = new GPIOClass("4");	// Create new GPIO object to be attached to  GPIO4
    gpio4->export_gpio(); 					// Export GPIO4
	gpio4->setdir_gpio("out");				// GPIO4 set to output

	if (timers == 0)
		timers = timers->getInstance(nmbtmrs);

	timers->init();		// Initialize timers
	timers->config();	// Configure timers to work for 10ms and 100ms counters

	for(;;)
	{
		timers->incTime();		// Always check if timers need to be incremented

		count++;
		if (timers->get10msTimer(tfirst) != 0)
		{
			gpio4->setval_gpio("1");
			if (timers->get10msTimer(tfirst) >= 2)
				timers->clr10msTimer(tfirst);
		}
		else
		{
			gpio4->setval_gpio("0");
		}
	}
	return 0;
}