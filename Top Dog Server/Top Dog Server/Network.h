//Blake Sullivan - Network.h
#ifndef NETWORK_H
#define NETWORK_H

#include "SDL.h"
#include "SDL_net.h"
#include "PacketHeader.h"
//using namespace std;

class NetManager
{
private:
	UDPsocket socket;
	UDPpacket* packet;

public:
	NetManager();
	~NetManager();

	void OpenPort(int iPort);
	void AllocPacket(int iSize);
	void SendString(char* message, IPaddress destination);
	void SendStruct(basePacket* bp, IPaddress destination, int iSize);
	IPaddress ResolveHost(char* ipAdd, int iPort);

	UDPsocket GetSocket();
	UDPpacket* GetPacket();
};

#endif