//Blake Sullivan - NetworkClient.cpp
#include "NetworkClient.h"

NetworkClient::NetworkClient()
{
	SetName("");
	SetIsHost(false);
	SetCharSelected(-1);
	SetIsJoined(false);
	SetMapID(-1);
	SetServerID(-1);
	SetServerName("");
}
NetworkClient::~NetworkClient()
{
}

void NetworkClient::Init(string n, bool h, int c, bool j)
{
	SetName(n);
	SetIsHost(h);
	SetCharSelected(c);
	SetIsJoined(j);
	SetMapID(-1);
	SetServerID(-1);
	SetServerName("");
	m_NM.OpenPort(0);
	//cout << "Nc Init." << endl;
	//cout << "Server Address host: " << m_ServerAddress.host << " Port: " << m_ServerAddress.port << endl;
	m_ServerAddress = m_NM.ResolveHost("255.255.255.255", 2000);
	//cout << "Server Address host: " << m_ServerAddress.host << " Port: " << m_ServerAddress.port << endl;

	char buffer[255]; for (int i = 0; i < 255; i++) {buffer[i] = ' ';}
	for (int i = 0; i < 6; i++)
	{
		SetCharacter(i, -1, buffer);
	}
}

void NetworkClient::Send(basePacket* bPacket, int size)
{
	//cout << "Server Address host: " << m_ServerAddress.host << " Port: " << m_ServerAddress.port << endl;
	m_NM.SendStruct(bPacket, m_ServerAddress, size);
	/*switch (bPacket->id)
	{
	case CLIENT_BROADCAST:
	break;
	case CLIENT_NEW_USER:
	break;
	case CLIENT_MESSAGE:
	break;
	case PLAYER_UPDATE:
	break;
	case PLAYER_REFRESH:
	break;
	case CLIENT_SETUP:
	break;

	default:
		cout << "Invalid ID." << endl;
	}*/
}
bool NetworkClient::Receive()
{
	bool bRec = false;
	if (SDLNet_UDP_Recv(m_NM.GetSocket(), m_NM.GetPacket()))
	{
		//cout << "Received Packet" << endl;
		SetPacketReceived((basePacket*)m_NM.GetPacket()->data);
		bRec = true;
	}
	return bRec;
}

void NetworkClient::SetName(string n)
{
	m_sName = n;
}
void NetworkClient::SetIsHost(bool h)
{
	m_bIsHost = h;
}
void NetworkClient::SetCharSelected(int c)
{
	m_iCharSelected = c;
}
void NetworkClient::SetIsJoined(bool j)
{
	m_bIsJoined = j;
}
void NetworkClient::SetServerAddress(IPaddress sa)
{
	m_ServerAddress = sa;
}
void NetworkClient::SetServerAddress(string svrIP)
{
	char tempIP[255];
	sprintf(tempIP, svrIP.c_str());
	m_ServerAddress = m_NM.ResolveHost(tempIP, 2000);
}

string NetworkClient::GetName()
{
	return m_sName;
}
bool NetworkClient::GetIsHost()
{
	return m_bIsHost;
}
int NetworkClient::GetCharSelected()
{
	return m_iCharSelected;
}
bool NetworkClient::GetIsJoined()
{
	return m_bIsJoined;
}
IPaddress NetworkClient::GetServerAddress()
{
	return m_ServerAddress;
}

NetworkManager* NetworkClient::GetNetworkManager()
{
	return &m_NM;
}

void NetworkClient::SetPacketReceived(basePacket* bp)
{
	m_bpReceived = bp;
}
basePacket* NetworkClient::GetPacketReceived()
{
	return m_bpReceived;
}

string NetworkClient::GetIPFromServerAdd(IPaddress ip)
{
	char cTemp[255];
	string sTemp = "";
	sprintf(cTemp, "%d.%d.%d.%d!", ip.host&0xff, (ip.host>>8)&0xff, (ip.host>>16)&0xff, (ip.host>>24)&0xff);
	
	//cout << "cTemp: " << cTemp << "." << endl;
	for (int i = 0; i < 255; i++)
	{
		if (cTemp[i] == '!')
		{break;}
		sTemp += cTemp[i];
	}
	//cout << "sTemp: " << sTemp << "." << endl;

	return sTemp;
}

void NetworkClient::AddToName(string atn)
{
	m_sName += atn;
}
void NetworkClient::AddToName(char c)
{
	m_sName = m_sName + c;
}

void NetworkClient::SetMapID(int mid)
{
	m_iMapID = mid;
}
void NetworkClient::SetServerID(int sid)
{
	m_iMyServerID = sid;
}

int NetworkClient::GetMapID()
{
	return m_iMapID;
}
int NetworkClient::GetServerID()
{
	return m_iMyServerID;
}

void NetworkClient::SetServerName(string sn)
{
	m_sServerName = sn;
}
string NetworkClient::GetServerName()
{
	return m_sServerName;
}

void NetworkClient::SetCharacter(int id, int cid, char name[255])
{
	string tempName;
	m_aServerCharacters[id].charID = cid;
	//cout << "In SetCharacter. Name: " << name << endl;
	for (int i = 0; i < 255; i++)
	{
		if (name[i] == '#')
		{break;}
		else
		{
			tempName = tempName + name[i];
		}
	}
	//cout << "In SetCharacter. tempName: " << tempName << endl;
	m_aServerCharacters[id].playerName = tempName;	
}
ServerCharacter& NetworkClient::GetCharacter(int id)
{
	return m_aServerCharacters[id];
}

void NetworkClient::SetScore(int s)
{
	m_iScore = s;
}

int NetworkClient::GetScore()
{
	return m_iScore;
}