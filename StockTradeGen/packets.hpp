#ifndef PACKETS_H
#define PACKETS_H

#include "comm.hpp"

class Packets
{
	private:
		Comm *uart;
		int request_que[100];
		int pkts_in_que;
		int pkts_que_pix;
		int pkts_que_gix;

	public:
		Packets();
		void generate(void);
		void createPacket(int packetNmb);
		int enquePktRequest(int pkt_no);
		int dequePktRequest(void);
};

#endif