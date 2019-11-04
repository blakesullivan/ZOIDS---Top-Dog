//Blake Sullivan - NetworkManager.h
#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

//#include "SDL.h"
//#include "SDL_net.h"
#include "PacketHeader.h"
#include <iostream>
using std::cout;
using std::endl;
//using namespace std;

class NetworkManager
{
private:
	UDPsocket socket;
	UDPpacket* packet;

public:
	NetworkManager();
	~NetworkManager();

	void OpenPort(int iPort);
	void AllocPacket(int iSize);
	void SendString(char* message, IPaddress destination);
	void SendStruct(basePacket* bp, IPaddress destination, int iSize);
	IPaddress ResolveHost(char* ipAdd, int iPort);

	UDPsocket GetSocket();
	UDPpacket* GetPacket();
};

#endif