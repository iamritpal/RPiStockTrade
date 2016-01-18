//*****************************************
//	Software Engineer - Amritpal Singh
//	Date - 01-17-2016
//*****************************************

#include <iostream>
#include "comm.hpp"
#include "timers.hpp"
#include "GPIOClass.hpp"
#include "packets.hpp"
#include "globals.h"

// g++ -o main main.cpp timers.cpp

enum Timer { 
	tfirst,
	tsecond,
	tthird,
	nmbtmrs
};

Timers *timers = 0;

Comm *uart = 0;

int packetInBuff=0;

int main(void)
{
	int i=0;

	GPIOClass* gpio4 = new GPIOClass("4");	// Create new GPIO object to be attached to  GPIO4
    gpio4->export_gpio(); 					// Export GPIO4
	gpio4->setdir_gpio("out");				// GPIO4 set to output

	
	// Get an instance of the timers class
	timers = timers->getInstance(nmbtmrs);

	timers->init();		// Initialize timers
	timers->config();	// Configure timers to work for 10ms and 100ms counters

	// Uart initialize and configure
	uart = uart->getInstance(COMMBUFFSIZE);
	uart->init();
	uart->config();

	// gpio4->setval_gpio("1");		// Turn ON Pin4
	// gpio4->setval_gpio("0");		// Turn OFF Pin4

	// Packets generator object
	Packets packets;

	for(;;)
	{
		timers->incTime();		// Always check if timers need to be incremented

		if (timers->get10msTimer(tfirst) != 0)
		{
			if (packetInBuff == 0)
			{
				packets.generate();
				packetInBuff = 1;		
			}
			if (timers->get10msTimer(tfirst) >= 2)
			{
				uart->transmit();
				timers->clr10msTimer(tfirst);
				packetInBuff = 0;
			}
		}
	}
	return 0;
}

