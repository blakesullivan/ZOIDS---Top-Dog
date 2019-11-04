//Blake Sullivan - Join.h
#ifndef JOIN_H
#define JOIN_H

#include "Scene.h"
#include "ButtonManager.h"
#include "NetworkClient.h"

class Join : public Scene
{
private:
	const static int MCS_IMAXSERVERS = 11;
	SDL_Surface* m_Background;
	ButtonManager* m_pBM;
	MyText* m_pMT;
	NetworkClient* m_pNC;
	bool m_bIsRefreshing;
	int m_iNumServers;
	
	ServerButtons m_aSvrButtons[MCS_IMAXSERVERS];
	string m_sChatMessage;
	string m_asMessages[20]; //array of messages

public:
	Join();
	Join(MyText* mt, NetworkClient* nc);
	~Join() {};

	void Init();
	void Update(SDL_Surface* screen, float fDeltaTime);
	void Draw(SDL_Surface* screen, float fDeltaTime);
	//int Status();
	void Dispose();

	virtual void MouseUpEvent(SDL_Event* event);
	virtual void MouseDownEvent (SDL_Event* event);
	virtual void KeyUpEvent(SDL_Event* event);
	virtual void KeyDownEvent(SDL_Event* event);

	void AddButtons();
	void UpdateButtons();
	void ManageButtonPress();

	void RefreshServerList();
	void ResponseToReceive();
	void ConnectToServer(int iSvrNum);
	void SetupServerButtons();
	void SetupConnectedUser();

	void AddLetterToName(int addToButton);
	void SetChatMessage(string cm);
	void AddToChatMessage(string atcm);
	void AddToChatMessage(char c);
	string GetChatMessage();

	void SendChatMessage(string msg);
	void AddToChatWindow();
};

#endif