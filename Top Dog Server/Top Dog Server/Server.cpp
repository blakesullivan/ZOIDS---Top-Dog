//Blake Sullivan - Server.cpp
#include "Server.h"

Server::Server()
{
	m_iNumConnected = 0;
	net.OpenPort(2000);
	for (int i = 0; i < 6; i++)
	{
		m_aPlayer[i].charID = -1;
	}
	//RunServer();
}

int Server::RunServer()
{
	SetupServer();
	//cout << "Please enter Server Name: ";
	//cin.getline(m_cServerName, 255);

	printf("Server: %s is ready.\n", m_cServerName);

	char cBuffer[255];
	/* Main loop */
	m_iQuit = 0;
	while (!m_iQuit)
	{
		/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
		while (SDLNet_UDP_Recv(net.GetSocket(), net.GetPacket()))
		{
			basePacket* tempData = (basePacket*)net.GetPacket()->data;

			//printf("Packet reveived: ID = %d\n", tempData->id);
			
			if (tempData->id == CLIENT_BROADCAST)//(cBuffer[0] == '@')
			{
				BroadcastResponse();
			}
			else if (tempData->id == CLIENT_NEW_USER)
			{
				NewUserResponse();
			}
			else if (tempData->id == CLIENT_MESSAGE) //Normal Message
			{
				ChatResponse();
			}
			else if (tempData->id == CLIENT_CHARACTER)
			{
				CharacterResponse();
			}
			else if (tempData->id == CLIENT_ALL_CHARACTER)
			{
				SendAllCharacters();
			}
			else if (tempData->id == PLAYER_UPDATE)
			{
				UpdateMovement();
			}
			else if (tempData->id == PLAYER_SHOOT)
			{
				SendBullet();
			}
			
			/* Quit if packet contains "quit" */
			if (!strcmp((char *)net.GetPacket()->data, "quit"))
				m_iQuit = 1;
		}		
	}
 
	/* Clean and exit */
	net.~NetManager();
	SDLNet_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}

void Server::SetupServer()
{
	bool bExit = false;

	cout << "Waiting for Server Details." << endl;
	do
	{
		//cout << "TEsting do." << endl;
		if (SDLNet_UDP_Recv(net.GetSocket(), net.GetPacket()))
		{
			cout << "Got packet in SetupServer" << endl;
			basePacket* tempData = (basePacket*)net.GetPacket()->data;
			if (tempData->id == CLIENT_SETUP)
			{
				setupPacket* sData = (setupPacket*)tempData;
				
				sprintf(m_cServerName, sData->serverName);
				m_iMapID = sData->mapID;

				printf("Server Name: %s MapID: %d\n", m_cServerName, m_iMapID);
				bExit = true;
			}
		}
	}while (bExit == false);
}

void Server::BroadcastResponse()
{
	srData = new serverResponsePacket();
	srData->id = SERVER_RESPONSE;
	sprintf(srData->serverName, m_cServerName);

	net.SendStruct((basePacket*)srData, net.GetPacket()->address, sizeof(*srData));
	delete[] srData;
}
void Server::NewUserResponse()
{
	char cIP[255];
	sprintf(cIP, "%d.%d.%d.%d", net.GetPacket()->address.host&0xff, (net.GetPacket()->address.host>>8)&0xff, (net.GetPacket()->address.host>>16)&0xff, (net.GetPacket()->address.host>>24)&0xff);

	cpData = (connectPacket*)net.GetPacket()->data;

	printf ("Connecting packet: %s from: %s\n", cpData->userName, cIP);
	
	if (m_iNumConnected < 6)
	{
		sprintf(m_aPlayer[m_iNumConnected].userNames, cpData->userName);

		m_aipAddress[m_iNumConnected].host = net.GetPacket()->address.host;
		m_aipAddress[m_iNumConnected].port = net.GetPacket()->address.port;
		
		mapData = new mapPacket();
		mapData->id = SERVER_NEW_USER;
		mapData->numConnected = m_iNumConnected;
		mapData->mapID = m_iMapID;

		net.SendStruct((basePacket*)mapData, m_aipAddress[m_iNumConnected], sizeof(*mapData));

		delete[] mapData;

		m_iNumConnected++;

		for (int i = 0; i < m_iNumConnected; i++)
		{
			messagePacket* smData = new messagePacket();

			smData->id = SERVER_MESSAGE;
			sprintf(smData->message, "%s successfully connected to %s#" , m_aPlayer[m_iNumConnected-1].userNames, m_cServerName);

			//cout << "Data message: " << smData->message << endl;

			net.SendStruct((basePacket*)smData, m_aipAddress[i], sizeof(*smData));
			delete[] smData;
		}
	}
	else
	{
		messagePacket* smData = new messagePacket();

		smData->id = SERVER_MESSAGE;
		sprintf(smData->message, "Server list full, try again later.");

		//cout << "Data message: " << smData->message << endl;

		net.SendStruct((basePacket*)smData, net.GetPacket()->address, sizeof(*smData));
		delete[] smData;
	}
}
void Server::ChatResponse()
{
	messagePacket* mData = (messagePacket*)net.GetPacket()->data;
	int iCurrNum = mData->userID;

	//printf("%s > %s\n", m_aPlayer[iCurrNum].userNames, mData->message);

	sprintf(m_cStringBuffer, "%s > %s", m_aPlayer[iCurrNum].userNames, mData->message);
	//printf("Sending to User: %s\n", m_cStringBuffer);

	for(int i = 0; i < m_iNumConnected; i++)
	{
		messagePacket* smData = new messagePacket();

		smData->id = SERVER_MESSAGE;
		sprintf(smData->message, "%s#" , m_cStringBuffer);

		//cout << "Data message: " << smData->message << endl;

		net.SendStruct((basePacket*)smData, m_aipAddress[i], sizeof(*smData));
		delete[] smData;
	}
}
void Server::CharacterResponse()
{
	characterPacket* cData = (characterPacket*)net.GetPacket()->data;
	int iCurrNum = cData->userID;

	m_aPlayer[iCurrNum].charID = cData->charID;
	cout << "Character Connect: userID: " << cData->userID << " charID: " << cData->charID << endl; 

	for(int i = 0; i < m_iNumConnected; i++)
	{
		characterConnectedPacket* rcData = new characterConnectedPacket();

		rcData->id = SERVER_CHARACTER;
		rcData->userID = cData->userID;
		rcData->charID = cData->charID;
		sprintf(rcData->userName, "%s#", m_aPlayer[iCurrNum].userNames);

		net.SendStruct((basePacket*)rcData, m_aipAddress[i], sizeof(*rcData));
		delete[] rcData;
	}
}

void Server::SendAllCharacters()
{
	for (int j = 0; j < m_iNumConnected; j++)
	{
		for(int i = 0; i < 6; i++)
		{
			if (m_aPlayer[i].charID > -1)
			{
				characterConnectedPacket* rcData = new characterConnectedPacket();

				rcData->id = SERVER_CHARACTER;
				rcData->userID = i;
				rcData->charID = m_aPlayer[i].charID;
				sprintf(rcData->userName, "%s#", m_aPlayer[i].userNames);
				cout << "j: " << j << " i: " << i << " userID " << rcData->userID << " charID: " << rcData->charID << " userName: " << rcData->userName << endl;

				net.SendStruct((basePacket*)rcData, m_aipAddress[j], sizeof(*rcData));
				delete[] rcData;
			}
		}
	}
}

void Server::UpdateMovement()
{
	movePacket* mData = (movePacket*)net.GetPacket()->data;

	for (int i = 0; i < m_iNumConnected; i++)
	{
		if (i != mData->userID)
		{
			movePacket* rmData = new movePacket();

			rmData->id = mData->id;
			rmData->userID = mData->userID;
			rmData->charID = mData->charID;
			rmData->x = mData->x;
			rmData->y = mData->y;
			rmData->dir = mData->dir;
			rmData->shot = mData->shot;
			rmData->energyStart = mData->energyStart;
			rmData->health = mData->health;
			rmData->bullLeft = mData->bullLeft;
			rmData->engLeft = mData->engLeft;

			net.SendStruct((basePacket*)rmData, m_aipAddress[i], sizeof(*rmData));
			delete[] rmData;
		}
	}
	//cout << "Update sent!\n";
}

void Server::SendBullet()
{
	/*bulletPacket* bData = (bulletPacket*)net.GetPacket()->data;

	for (int i = 0; i < m_iNumConnected; i++)
	{
		if (i != bData->userID)
		{
			bulletPacket* rbData = new bulletPacket();

			rbData->id = bData->id;
			rbData->userID = bData->userID;

			net.SendStruct((basePacket*)rbData, m_aipAddress[i], sizeof(*rbData));
			delete[] rbData;
		}
	}*/
}