#ifndef PACKETS_H
#define PACKETS_H

#include "comm.hpp"

class Packets
{
	private:
		Comm *uart;

	public:
		Packets();
		void generate(void);
		void createPacket(int packetNmb);
};

#endif