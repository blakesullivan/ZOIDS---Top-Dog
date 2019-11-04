//Blake Sullivan - Character.h
#ifndef CHARACTERSELECT_H
#define CHARACTERSELECT_H

#include "Scene.h"
#include "ButtonManager.h"

class CharacterSelect : public Scene
{
private:
	SDL_Surface* m_Background;
	ButtonManager* m_pBM;
	MyText* m_pMT;

public:
	CharacterSelect();
	CharacterSelect(MyText* mt);

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