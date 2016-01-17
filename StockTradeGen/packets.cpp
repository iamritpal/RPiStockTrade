#include <iostream>
#include "packets.hpp"
#include "globals.h"

Packets::Packets()
{
	uart = uart->getInstance(COMMBUFFSIZE);
}

void Packets::generate(void)
{
	createPacket(1);
}

void Packets::createPacket(int packetNmb)
{
	uart->clrTxBuffer();

	// Every packet has the following byte
	uart->addTxByte('P');				// Start of frame byte

	uart->addTxByte(0x01);				// Source address		0x01 = Generator
										//						0x02 = Processor

	uart->addTxByte(0x02);				// Destination address	0x01 = Generator
										//						0x02 = Processor

	uart->addTxByte(0);					// Skip packet length byte, set later

	switch(packetNmb)
	{
		case 1:
			uart->addTxByte(packetNmb);
			uart->addTxByte(0xAA);			// Test payload byte 1
			uart->addTxByte(0xAB);			// Test payload byte 2
			uart->addTxByte(0xAC);			// Test payload byte 3
			uart->addTxByte(0xAD);			// Test payload byte 4
			uart->addTxByte(0xAE);			// Test payload byte 5
			uart->addTxByte(0xAF);			// Test payload byte 6
			break;

		default:
			break;
	}
	uart->addTxByte('@');				// End of frame
	uart->setTxPacketLength();
}