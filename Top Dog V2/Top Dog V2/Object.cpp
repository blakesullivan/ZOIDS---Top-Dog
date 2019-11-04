//Blake Sullivan - Object.cpp
#include "Object.h"
Object::Object()
{
	SetID(-1);
	SetType(-1);
	SetState(-1);
	SetX(0);
	SetY(0);
	SetSize(0);
	SetDamage(0);
	m_Surface = NULL;
}

void Object::SetID(int id)
{
	m_iID = id;
}
void Object::SetType(int t)
{
	m_iType = t;
}
void Object::SetState(int s)
{
	m_iState = s;
}
void Object::SetX(float x)
{
	m_fX = x;
}
void Object::SetY(float y)
{
	m_fY = y;
}
void Object::SetSize(float r)
{
	m_fSize = r;
}
void Object::SetDamage(int d)
{
	m_iDamage = d;
}
void Object::SetSurface(std::string s)
{
	m_Surface = SDL_LoadBMP(s.c_str());
	SDL_SetColorKey(m_Surface, SDL_SRCCOLORKEY, SDL_MapRGB(m_Surface->format, 255, 0, 255));
}

int Object::GetID()
{
	return m_iID;
}
int Object::GetType()
{
	return m_iType;
}
int Object::GetState()
{
	return m_iState;
}
float Object::GetX()
{
	return m_fX;
}
float Object::GetY()
{
	return m_fY;
}
float Object::GetSize()
{
	return m_fSize;
}
int Object::GetDamage()
{
	return m_iDamage;
}

SDL_Surface* Object::GetSurface()
{
	return m_Surface;
}