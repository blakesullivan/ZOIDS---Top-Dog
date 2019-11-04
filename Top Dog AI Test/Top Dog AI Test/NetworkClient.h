//Blake Sullivan - NetworkClient.h
#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include "NetworkManager.h"
#include <string>
using std::string;

class NetworkClient
{
private:
	string m_sName;
	bool m_bIsHost;
	int m_iCharSelected, m_iMapID, m_iMyServerID;
	bool m_bIsJoined;
	NetworkManager m_NM;
	IPaddress m_ServerAddress;
	ServerCharacter m_aServerCharacters[6];
	basePacket* m_bpReceived;
	string m_sServerName;

public:
	NetworkClient();
	~NetworkClient();

	void Init(string n, bool h, int c, bool j);

	void Send(basePacket* bPacket, int size);
	bool Receive();

	void SetName(string n);
	void SetIsHost(bool h);
	void SetCharSelected(int c);
	void SetIsJoined(bool j);
	void SetServerAddress(IPaddress sa);
	void SetServerAddress(string svrIP);
	void SetPacketReceived(basePacket* bp);

	string GetName();
	bool GetIsHost();
	int GetCharSelected();
	bool GetIsJoined();
	IPaddress GetServerAddress();
	basePacket* GetPacketReceived();
	string GetIPFromServerAdd(IPaddress ip);

	NetworkManager* GetNetworkManager();
	void AddToName(string atn);
	void AddToName(char c);

	void SetMapID(int mid);
	void SetServerID(int sid);

	int GetMapID();
	int GetServerID();

	void SetServerName(string sn);
	string GetServerName();

	void SetCharacter(int id, int cid,  char name[255]);
	ServerCharacter& GetCharacter(int id);
};

#endif