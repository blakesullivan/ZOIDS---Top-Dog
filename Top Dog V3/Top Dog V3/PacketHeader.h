//Blake Sullivan - PacketHeader.h
#ifndef PACKETHEADER_H
#define PACKETHEADER_H

#include "SDL_net.h"
#include <string>

const int STRING_SIZE = 100;

enum NetworkPackets
{
	CLIENT_BROADCAST = 240,
	SERVER_RESPONSE = 241,
	CLIENT_NEW_USER = 242,
	SERVER_NEW_USER = 243,
	CLIENT_MESSAGE = 244,
	SERVER_MESSAGE = 245,
	PLAYER_UPDATE = 246,
	PLAYER_REFRESH = 247,
	CLIENT_SETUP = 248,
	MAP_MESSAGE = 249,
	CLIENT_ALL_CHARACTER = 2409,
	CLIENT_CHARACTER = 2410,
	SERVER_CHARACTER = 2411,
	PLAYER_SHOOT = 2412
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
struct movePacket
{
	int id;
	int userID;
	int charID;
	float x;
	float y;
	float dir;
	bool shot;
	bool energyStart;
	float health;
	float bullLeft;
	float engLeft;
};
#pragma pack(pop)

/*#pragma pack(1)
struct bulletPacket
{
	int id;
	int userID;
};
#pragma pack(pop)*/

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