//Blake Sullivan - NetworkManager.cpp
#include "NetworkManager.h"

NetworkManager::NetworkManager()
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
NetworkManager::~NetworkManager()
{
	SDLNet_FreePacket(packet);
}

void NetworkManager::OpenPort(int iPort)
{
	/* Open a socket */
	if (!(socket = SDLNet_UDP_Open(iPort)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
}

void NetworkManager::AllocPacket(int iSize)
{
	/* Make space for the packet */
	if (!(packet = SDLNet_AllocPacket(iSize)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
}

void NetworkManager::SendString(char* message, IPaddress destination)
{
	sprintf((char*)packet->data, message);
	packet->len = strlen((char *)packet->data) + 1;

	packet->address.host = destination.host;
	packet->address.port = destination.port;
	SDLNet_UDP_Send(socket, -1, packet); /* This sets the p->channel */
}

void NetworkManager::SendStruct(basePacket* bp, IPaddress destination, int iSize)
{
	//cout << "Sending packet from NM: " << bp->id << endl;
	memcpy(GetPacket()->data, bp, iSize);
	GetPacket()->len = iSize + 1;

	GetPacket()->address.host = destination.host;
	GetPacket()->address.port = destination.port;
	SDLNet_UDP_Send(GetSocket(), -1, GetPacket()); /* This sets the p->channel */
}

IPaddress NetworkManager::ResolveHost(char* ipAdd, int iPort)
{
	IPaddress srvadd;

	/* Resolve server name  */
	if (SDLNet_ResolveHost(&srvadd, ipAdd, iPort))
	{
		fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", ipAdd, iPort, SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	//cout << "Resolving Server Address host: " << srvadd.host << " Port: " << srvadd.port << endl;
	return srvadd;
}

UDPsocket NetworkManager::GetSocket()
{
	return socket;
}
UDPpacket* NetworkManager::GetPacket()
{
	return packet;
}