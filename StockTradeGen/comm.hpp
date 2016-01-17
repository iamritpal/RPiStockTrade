//*****************************************
//	Software Engineer - Amritpal Singh
//	Date - 01-17-2016
//*****************************************


#ifndef COMM_H
#define COMM_H

#include <vector>

class Comm
{
	private:
		int maxSize;
		int rxIx;
		int txIx;
		std::vector<unsigned short> rxbuffer;
		std::vector<unsigned short> txbuffer;


	public:
		Comm(int max);
		void init(void);
		void clrTxBuffer(void);
		void clrRxBuffer(void);
		void addTxByte(unsigned short byte);
		void addRxByte(unsigned short byte);
		void send(void);
		void recieve(void);
};

#endif