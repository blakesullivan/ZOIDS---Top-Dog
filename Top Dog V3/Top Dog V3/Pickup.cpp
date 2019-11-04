//Blake Sullivan - Pickup.cpp
#include "Pickup.h"

Pickup::Pickup()
{
	SetPickupType(-1);
	SetRespawnTimer(-1);
}

void Pickup::Init(int pt, float x, float y)
{
	SetPickupType(pt);
	SetID(pt);
	SetX(x);
	SetY(y);
	SetTypeDifferences(pt);
	SetRespawnTimer(0);
}

void Pickup::Draw(SDL_Surface* screen, float fDeltaTime, float winX, float winY)
{
	SDL_Rect sclip, dclip;
	sclip.x = 0; sclip.y = 0; sclip.w = GetSize(); sclip.h = GetSize();

	dclip.x = GetX() - (GetSize()/2) - winX; dclip.y = GetY() - (GetSize()/2) - winY;
	dclip.w = GetSize(); dclip.h = GetSize();

	SDL_BlitSurface(GetSurface(), &sclip, screen, &dclip);
	//rectangleRGBA(screen, GetX() - (GetSize() / 2), GetY() - (GetSize() / 2), GetX() + (GetSize() / 2), GetY() + (GetSize() / 2), 0, 0, 0, 255);

}
void Pickup::Update(float fDeltaTime)
{
	if (GetState() == stateDead)
	{
		SetState(stateRespawn);
	}
	else if (GetState() == stateRespawn && GetRespawnTimer() <= 10)
	{
		SetRespawnTimer(GetRespawnTimer() + fDeltaTime);
	}
	else if (GetState() == stateRespawn && GetRespawnTimer() > 10)
	{
		SetRespawnTimer(0);
		SetState(stateAlive);
		cout << "Pickup Alive Again." << endl;
	}

}
void Pickup::Collide(Object* obj)
{
	if (obj->GetType() == typeCharacter)
		{SetState(stateDead);}
}
void Pickup::Dispose()
{
	SDL_FreeSurface(GetSurface());
}

void Pickup::SetTypeDifferences(int pt)
{
	switch (pt)
	{
	case -1:
	case 0:
		SetSize(32);
		SetDamage(-100);
		SetSurface("Images/Health.png");
	break;
	case 1:
		SetSize(32);
		SetDamage(0);
		SetSurface("Images/Ammo1.png");
	break;
	case 2:
		SetSize(32);
		SetDamage(0);
		SetSurface("Images/Ammo2.png");
	break;
	}
}

void Pickup::SetPickupType(int pt)
{
	m_iPickupType = pt;
}
void Pickup::SetRespawnTimer(float rt)
{
	m_fRespawnTimer = rt;
}
int Pickup::GetPickupType()
{
	return m_iPickupType;
}
float Pickup::GetRespawnTimer()
{
	return m_fRespawnTimer;
}