//Blake Sullivan - PacketHeader.h
#ifndef PACKETHEADER_H
#define PACKETHEADER_H

#include "SDL_net.h"
#include <string>

const int STRING_SIZE = 100;

enum NetworkPackets
{
	CLIENT_BROADCAST = 0,
	SERVER_RESPONSE = 1,
	CLIENT_NEW_USER = 2,
	SERVER_NEW_USER = 3,
	CLIENT_MESSAGE = 4,
	SERVER_MESSAGE = 5,
	PLAYER_UPDATE = 6,
	PLAYER_REFRESH = 7,
	CLIENT_SETUP = 8,
	MAP_MESSAGE = 9,
	CLIENT_CHARACTER = 10,
	SERVER_CHARACTER = 11,
	PLAYER_SHOOT = 12
};

#pragma pack(1)
struct basePacket
{
	int id;
};
#pragma pack(pop)

#pragma pack(1)
struct serverResponsePacket
{
	int id;
	char serverName[255];
};
#pragma pack(pop)

#pragma pack(1)
struct connectPacket
{
	int id;
	char userName[255];
};
#pragma pack(pop)

#pragma pack(1)
struct newUserPacket
{
	int id;
	int userID;
};
#pragma pack(pop)

#pragma pack(1)
struct messagePacket
{
	int id;
	int userID;
	char message[255];
};
#pragma pack(pop)

#pragma pack(1)
struct movePacket
{
	int id;
	float x;
	float y;
	float dir;
	int userID;
};
#pragma pack(pop)

#pragma pack(1)
struct setupPacket
{
	int id;
	char serverName[255];
	int mapID;
};
#pragma pack(pop)

#pragma pack(1)
struct mapPacket
{
	int id;
	int mapID;
	int numConnected;
};
#pragma pack(pop)

#pragma pack(1)
struct characterPacket
{
	int id;
	int userID;
	int charID;
};
#pragma pack(pop)

#pragma pack(1)
struct characterConnectedPacket
{
	int id;
	int userID;
	int charID;
	char userName[255];
};
#pragma pack(pop)

#pragma pack(1)
struct bulletPacket
{
	int id;
	int userID;
};
#pragma pack(pop)

struct ServerButtons
{
	int buttID;
	IPaddress srvAdd;
};
struct ServerCharacter
{
	int charID;
	std::string playerName;
};
#endif