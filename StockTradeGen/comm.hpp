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
		unsigned short rxIx;
		unsigned short txIx;
		int uart0_filestream;
		std::vector<unsigned char> rxbuffer;
		std::vector<unsigned char> txbuffer;
		static Comm* m_pInstance;
		Comm(int max);

	public:
		Comm* getInstance(int max);
		void init(void);
		void config(void);
		void clrTxBuffer(void);
		void clrRxBuffer(void);
		void addTxByte(unsigned char byte);
		void addRxByte(unsigned char byte);
		void setTxPacketLength(void);
		void send(void);
		void recieve(void);
		void transmit(void);
		void printtxbuff(void);
};

#endif