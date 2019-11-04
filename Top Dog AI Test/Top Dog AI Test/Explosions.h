//Blake Sullivan - Explosions.h
#ifndef EXPLOSIONS_H
#define EXPLOSIONS_H

#include "Object.h"

class Explosions : public Object
{
private:
	//SDL_Surface* m_pSurface;
	//float m_fX, m_fY;
	float m_fTimer;
	int m_iOwner;
	int m_iPicSize;
	//int m_iState;
	
public:
	Explosions();

	void Init(int type, int id, int o, float x, float y, float t = 10);

	void Draw(SDL_Surface* screen, float fDeltaTime, float winX, float winY);
	void Update(float fDeltaTime);
	void Collide(Object* obj);
	void Dispose();

	//void SetX(float);
	//void SetY(float);
	void SetTimer(float);
	void SetOwner(int);
	void SetPicSize(int);
	//void SetState(int);

	//float GetX();
	//float GetY();
	float GetTimer();
	int GetOwner();
	int GetPicSize();
	//int GetState();
};

#endif