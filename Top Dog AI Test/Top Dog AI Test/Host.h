//Blake Sullivan - Host.h
#ifndef HOST_H
#define HOST_H

#include "Scene.h"
#include "ButtonManager.h"
#include "MyText.h"
#include "NetworkClient.h"

class Host : public Scene
{
private:
	SDL_Surface* m_Background;
	ButtonManager* m_pBM;
	MyText* m_pMT;
	NetworkClient* m_pNC;
	int m_iMapID;
	SDL_Surface* m_Map;
	string m_sServerName;

public:
	Host();
	Host(MyText* mt, NetworkClient* nc);
	~Host() {};

	void Init();
	void Update(SDL_Surface* screen, float fDeltaTime);
	void Draw(SDL_Surface* screen, float fDeltaTime);
	//int Status();
	void Dispose();

	virtual void MouseUpEvent(SDL_Event* event);
	virtual void MouseDownEvent (SDL_Event* event);
	virtual void KeyUpEvent(SDL_Event* event);
	virtual void KeyDownEvent(SDL_Event* event);

	void ManageButtonPress();
	void AddMenuButtons();
	void AddOptions();
	void AddLetterToName(int addToButton);
	void DrawText(SDL_Surface* screen);

	void SetupHostWithServer();

	void SetServerName(string sn);
	void AddToServerName(string atsn);
	void AddToServerName(char c);
	string GetServerName();
};
#endif