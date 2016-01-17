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
		static Comm* m_pInstance;
		Comm(int max);

	public:
		Comm* getInstance(int max);
		void init(void);
		void config(void);
		void clrTxBuffer(void);
		void clrRxBuffer(void);
		void addTxByte(unsigned short byte);
		void addRxByte(unsigned short byte);
		void send(void);
		void recieve(void);
};

#endif