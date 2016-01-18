#include <iostream>
#include "packets.hpp"
#include "globals.h"

Packets::Packets()
{
	uart = uart->getInstance(COMMBUFFSIZE);
}

void Packets::generate(void)
{
	static int i=1;
	createPacket(i);
	if (i == 1)
		i = 2;
	else
		i = 1;
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