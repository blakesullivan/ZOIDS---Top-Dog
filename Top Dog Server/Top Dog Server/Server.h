//Blake Sullivan - Server.h
#ifndef SERVER_H
#define SERVER_H

#include "Network.h"
#include <iostream>
#include <string>
using namespace std;

class Server
{
private:
	const static int MCS_IMAXUSERS = 6;
	NetManager net;

	struct Player
	{
		int charID;
		char userNames[255];
	};
	Player m_aPlayer[6];
	
	IPaddress m_aipAddress[6];
	int m_iNumConnected;
	char m_cServerName[255];
	IPaddress m_ipServerAddress;
	int m_iQuit;
	char m_cStringBuffer[255];
	int m_iMapID;
	
	basePacket* pData;
	serverResponsePacket* srData;
	connectPacket* cpData;
	newUserPacket* nuData;
	messagePacket* mData;
	mapPacket* mapData;

public:
	Server();

	int RunServer();
	
	void SetupServer();
	void BroadcastResponse();
	void NewUserResponse();
	void ChatResponse();
	void CharacterResponse();
	void SendAllCharacters();
	void UpdateMovement();
	void SendBullet();
};

#endif