//*****************************************
//	Software Engineer - Amritpal Singh
//	Date - 01-17-2016
//*****************************************

#include <iostream>
#include "comm.hpp"

Comm* Comm::m_pInstance = NULL;

// Default constructor

Comm::Comm(int max)
{
	maxSize = max;
	rxbuffer.resize(maxSize);		// resize vector
	txbuffer.resize(maxSize);
}

Comm* Comm::getInstance(int max)
{
	if (!m_pInstance)   		// Only allow one instance of class to be generated.
		m_pInstance = new Comm(max);
	return m_pInstance;
}

void Comm::init(void)
{
	int i;
	txIx = 0;
	rxIx = 0;
	for (i=0;i<maxSize;i++)
	{
		rxbuffer[i] = 0;
		txbuffer[i] = 0;
	}
}

void Comm::clrTxBuffer(void)
{
	txIx = 0;
}

void Comm::addTxByte(unsigned short byte)
{
	txbuffer[txIx++] = byte;
}

void Comm::clrRxBuffer(void)
{
	rxIx = 0;
}

void Comm::addRxByte(unsigned short byte)
{
	rxbuffer[rxIx++] = byte;
}
