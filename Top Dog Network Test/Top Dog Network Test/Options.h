//Blake Sullivan - Options.h
#ifndef OPTIONS_H
#define OPTIONS_H

#include "Scene.h"
#include "ButtonManager.h"

class Options : public Scene
{
private:
	SDL_Surface* m_Background;
	SDL_Surface* m_Instructions;
	ButtonManager* m_pBM;
	MyText* m_pMT;

public:
	Options();
	Options(MyText* mt);
	~Options() {};

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
};

#endif