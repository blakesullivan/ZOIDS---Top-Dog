//Blake Sullivan - Splash.h
#ifndef PLAY_H
#define PLAY_H

#include "Scene.h"
#include "ButtonManager.h"
#include "MyText.h"
#include "Level.h"
class Play : public Scene
{
private:
	ButtonManager* m_pBM;
	MyText* m_pMT;
	Level* m_pLevel;
	int m_iMyID;
	float m_fWindowX, m_fWindowY;

public:
	Play();
	Play(MyText* mt);
	~Play() {};

	void Init();
	void Update(SDL_Surface* screen, float fDeltaTime);
	void Draw(SDL_Surface* screen, float fDeltaTime);
	//int Status();
	void Dispose();

	virtual void MouseUpEvent(SDL_Event* event);
	virtual void MouseDownEvent (SDL_Event* event);
	virtual void KeyUpEvent(SDL_Event* event);
	virtual void KeyDownEvent(SDL_Event* event);

	void AddAndSetButtons();
	void UpdateButtons();
	void ManageButtons();
};
#endif