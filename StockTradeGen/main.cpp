#include <iostream>
#include "timers.hpp"

// g++ -o main main.cpp timers.cpp

enum Timer { 
	tfirst,
	tsecond,
	tthird,
	nmbtmrs
};

Timers msTimers(nmbtmrs);		// Create ms timers

int main(void)
{
	int i=0;
	int count=0;

	msTimers.config();

	for(;;)
	{
		if (msTimers.getUpdateTime() != 0)
		{
			msTimers.incTime();
		}

		if (count >= 10)
		{
			count = 0;			
			std::cout << "tfirst = " << msTimers.getTimer(tfirst) << std::endl;
		}
	}

	/*

	while(i < 10)
	{
		msTimers.incTime();
		i++;
	}

	std::cout << msTimers.getTimer(0);
	*/
	return 0;
}