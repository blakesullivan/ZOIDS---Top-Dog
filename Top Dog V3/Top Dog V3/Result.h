//Blake Sullivan - Result.h
#ifndef RESULT_H
#define RESULT_H

#include "Scene.h"
#include "ButtonManager.h"

class Result : public Scene
{
private:
	SDL_Surface* m_Background;
	SDL_Surface* m_Avatars;
	ButtonManager* m_pBM;
	MyText* m_pMT;

public:
	Result();
	Result(MyText* mt);
	~Result() {};

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

	void DrawAvatars(SDL_Surface* screen);
};

#endif