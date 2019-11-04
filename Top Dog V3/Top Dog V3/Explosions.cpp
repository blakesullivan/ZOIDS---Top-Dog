//Blake Sullivan - Explosions.cpp
#include "Explosions.h"

Explosions::Explosions()
{
	SetX(0);
	SetY(0);
	SetTimer(0);
	SetOwner(0);
	SetSize(0);
	m_Surface = NULL;
}

void Explosions::Init(int type, int id, int o, float x, float y, float t)
{
	if (type == typeCharacter)
	{
		SetSurface("Images/Explosion2.png");
		SetSize(224);
		SetPicSize(256);
	}
	else
	{
		SetSurface("Images/Explosion.png");
		SetSize(96);
		SetPicSize(128);
	}

	SetID(id);
	SetType(typeExplosion);
	SetState(stateAlive);
	SetX(x);
	SetY(y);
	SetTimer(t);
	SetOwner(o);
	SetDamage(1);

	//cout << "Explosion: id: " << id << " x: " << x << " y: " << y << endl;
}

void Explosions::Draw(SDL_Surface* screen, float fDeltaTime, float winX, float winY)
{
	SDL_Rect sclip, dclip;

	sclip.x = static_cast<int>(GetTimer()) * GetPicSize();
	//cout << "Explosion timer: " << GetTimer() << " sclip.x: " << sclip.x << endl;
	sclip.y = 0; sclip.w = GetPicSize(); sclip.h = GetPicSize();

	dclip.x = GetX() - (winX + (GetPicSize()/2)); dclip.y = GetY() - (winY + (GetPicSize() / 2));
	dclip.w = GetPicSize(); dclip.h = GetPicSize();

	SDL_BlitSurface(GetSurface(), &sclip, screen, &dclip);
}

void Explosions::Update(float fDeltaTime)
{
	SetTimer(GetTimer() - 1);//(fDeltaTime * 4));
	if (GetTimer() <= 0)
	{
		SetState(stateDead);
	}
}
void Explosions::Collide(Object* obj)
{
}
void Explosions::Dispose()
{
	SDL_FreeSurface(GetSurface());
}

/*void Explosions::SetX(float x)
{
	m_fX = x;
}
void Explosions::SetY(float y)
{
	m_fY = y;
}*/
void Explosions::SetTimer(float t)
{
	m_fTimer = t;
}
void Explosions::SetOwner(int o)
{
	m_iOwner = o;
}
void Explosions::SetPicSize(int ps)
{
	m_iPicSize = ps;
}
//void Explosions::SetState(int)
//{
//}

/*float Explosions::GetX()
{
	return m_fX;
}
float Explosions::GetY()
{
	return m_fY;
}*/
float Explosions::GetTimer()
{
	return m_fTimer;
}
int Explosions::GetOwner()
{
	return m_iOwner;
}
int Explosions::GetPicSize()
{
	return m_iPicSize;
}
//int Explosions::GetState()
//{
//}