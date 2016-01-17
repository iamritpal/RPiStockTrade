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
		timers = timers->Instance(nmbtmrs);

	timers->config();

	for(;;)
	{
		timers->incTime();		// Always check if timers need to be incremented

		if (timers->get10msTimer(tfirst) != 0)
		{
			timers->clr10msTimer(tfirst);
			count++;
			if (count >= 10)
			{
				count = 0;
				std::cout << sec++ << std::endl;				
			}
		}
	}
	return 0;
}