//Blake Sullivan - Object.h
#ifndef OBJECT_H
#define OBJECT_H

#include "SDL_gfxPrimitives.h"
#include "SDL_rotozoom.h"
#include "SDL_image.h"
#include "StateHeader.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Object
{
protected:
	int m_iID;
	int m_iType;
	int m_iState;	//State of the object
	float m_fX, m_fY;
	float m_fSize;	//Circle Collision Detection, can be modified for Square
	float m_fDamage;	//Damage this object will do
	SDL_Surface* m_Surface;

public:
	Object();
	~Object() {};

	virtual void Draw(SDL_Surface* screen, float fDeltaTime, float winX, float winY) = 0;
	virtual void Update(float fDeltaTime) = 0;
	virtual void Collide(Object* obj) = 0;
	virtual void Dispose() = 0;

	void SetID(int);
	void SetType(int);
	void SetState(int);
	void SetX(float);
	void SetY(float);
	void SetSize(float);
	void SetDamage(int);
	void SetSurface(string);

	int GetID();
	int GetType() const;
	int GetState();
	float GetX();
	float GetY();
	float GetSize();
	int GetDamage();
	SDL_Surface* GetSurface();
};

#endif