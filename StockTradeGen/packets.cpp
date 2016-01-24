#include <iostream>
#include "packets.hpp"
#include "globals.h"

Packets::Packets()
{
	uart = uart->getInstance(COMMBUFFSIZE);
	stock = stock->getInstance();
	
	// Initialize packets queue
	pkts_in_que = 0;
	pkts_que_pix = 0;
	pkts_que_gix = 0;
}

void Packets::generate(void)
{
	int i;
	static int ix=0;
	static int putReq=0;

	i=dequePktRequest(); 
	if (i != 0)
		createPacket(i);
	else	// Queue is empty
	{
		if (putReq == 0)
		{
			putReq = 1;
			stock->requestUpdate();
		}
		else
		{
			if (putReq == 1)
			{
				if (stock->requestStatus() != 0)
					putReq = 2;
			}
			else
			{
				std::cout << "index = " << ix++ << std::endl; 
				for (i=0;i<10;i++)
				{
					stock->getStockInfo(i,&gstock);
					std::cout<<gstock.getStockPrice()<<std::endl;
				}
				putReq = 0;
			}
		}
	}
}

void Packets::createPacket(int packetNmb)
{
	static unsigned short test=0;
	
	uart->clrTxBuffer();		// Start off with clear tx buffer

	// Every packet has the following byte
	uart->addTxByte('P');				// Start of frame byte
	uart->addTxByte(0x01);				// Source address		0x01 = Generator
										//						0x02 = Processor
	uart->addTxByte(0x02);				// Destination address	0x01 = Generator
										//						0x02 = Processor
	uart->addTxByte(0);				// Skip packet length byte, set later

	switch(packetNmb)
	{
		case 1:
			uart->addTxByte(packetNmb);		// Packet Number
			uart->addTxByte('t');			// Test payload byte 1
			uart->addTxByte('a');			// Test payload byte 2
			uart->addTxByte('e');			// Test payload byte 3
			uart->addTxByte('s');			// Test payload byte 4
			uart->addTxByte('t');			// Test payload byte 5
			uart->addTxByte('t');			// Test payload byte 6
			break;

		case 2:
			uart->addTxByte(packetNmb);		// Packet Number
			uart->addTxByte(56);			// Price
			uart->addTxByte('A');			// Stock symbot 'A'
			uart->addTxByte('A');
			uart->addTxByte('P');
			uart->addTxByte('L');
			break;

		default:
			break;
	}
	uart->addTxByte('@');			// Test payload byte 6
	uart->setTxPacketLength();
}

int Packets::enquePktRequest(int pkt_no)
{
	if (pkts_in_que < 100)
	{
		pkts_que_pix++;
		if (pkts_que_pix >= 100)
			pkts_que_pix = 0;
		request_que[pkts_que_pix] = pkt_no;
		pkts_in_que++;
		return(1);
	}
	return(0);
}

int Packets::dequePktRequest(void)
{
	if (pkts_in_que != 0)
	{
		pkts_que_gix++;
		if (pkts_que_gix >= 100)
			pkts_que_gix = 0;
		pkts_in_que--;
		return(request_que[pkts_que_gix]);
	}
	return(0);
}
