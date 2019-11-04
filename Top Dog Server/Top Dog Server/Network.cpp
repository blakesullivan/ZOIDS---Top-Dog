//Blake Sullivan - Network.cpp
#include "Network.h"

NetManager::NetManager()
{
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	OpenPort(0);
	AllocPacket(512);
}
NetManager::~NetManager()
{
	SDLNet_FreePacket(packet);
	SDLNet_Quit();
}

void NetManager::OpenPort(int iPort)
{
	/* Open a socket */
	if (!(socket = SDLNet_UDP_Open(iPort)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
}

void NetManager::AllocPacket(int iSize)
{
	/* Make space for the packet */
	if (!(packet = SDLNet_AllocPacket(iSize)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
}

void NetManager::SendString(char* message, IPaddress destination)
{
	sprintf((char*)packet->data, message);
	packet->len = strlen((char *)packet->data) + 1;

	packet->address.host = destination.host;
	packet->address.port = destination.port;
	SDLNet_UDP_Send(socket, -1, packet); /* This sets the p->channel */
}

void NetManager::SendStruct(basePacket* bp, IPaddress destination, int iSize)
{
	memcpy(packet->data, bp, iSize);
	packet->len = iSize + 1;

	packet->address.host = destination.host;
	packet->address.port = destination.port;
	SDLNet_UDP_Send(socket, -1, packet); /* This sets the p->channel */
}

IPaddress NetManager::ResolveHost(char* ipAdd, int iPort)
{
	IPaddress srvadd;

	/* Resolve server name  */
	if (SDLNet_ResolveHost(&srvadd, ipAdd, iPort))
	{
		fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", ipAdd, iPort, SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	return srvadd;
}

UDPsocket NetManager::GetSocket()
{
	return socket;
}
UDPpacket* NetManager::GetPacket()
{
	return packet;
}