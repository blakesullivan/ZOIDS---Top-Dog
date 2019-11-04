//Blake Sullivan - Splash.h
#ifndef OPTIONS_H
#define OPTIONS_H

#include "Scene.h"
#include "ButtonManager.h"
#include "MyText.h"

class Host : public Scene
{
private:
	SDL_Surface* m_Background;
	ButtonManager* m_pBM;
	MyText* m_pMT;

public:
	Host();
	Host(MyText* mt);

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
	void AddLetterToName();
	void DrawText(SDL_Surface* screen);
};
#endif