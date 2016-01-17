#include <iostream>
#include "timers.hpp"

// g++ -o main main.cpp timers.cpp

enum Timer { 
	tfirst,
	tsecond,
	tthird,
	nmbtmrs
};

Timers timer(nmbtmrs);		// Create ms timers

int main(void)
{
	int i=0;
	int count=0, sec=0;

	timer.config();

	for(;;)
	{
		timer.incTime();

		if (timer.get10msTimer(tfirst) != 0)
		{
			timer.clr10msTimer(tfirst);
			count++;
			if (count >= 100)
			{
				count = 0;
				std::cout << sec++ << std::endl;				
			}
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