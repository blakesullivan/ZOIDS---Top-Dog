//Blake Sullivan - Bullet.cpp
#include "Bullet.h"
#include "Character.h"

Bullet::Bullet()
{
	SetBullType(-1);
	SetOwner(-1);
	SetMoveSpeed(-1);
	SetDirection(-1);
	SetLife(-1);
	SetMaxLife(-1);
	SetOX(-1);
	SetOY(-1);
	SetSize(-1);
}

void Bullet::Init(int o, int bt, float x, float y, float dir)
{
	SetOwner(o);
	SetBullType(bt);
	if (GetBullType() == btBullet)
		{SetSurface("B.bmp");}
	else
		{SetSurface("M.bmp");}
	SetX(x);
	SetY(y);
	SetDirection(dir);
	SetMoveSpeed(GetBulletSpeed(o));
	SetDamage(GetBulletDamage(o));
	SetLife(0);
	SetMaxLife(GetBulletMaxLife(o));
	SetOX(x);
	SetOY(y);
	SetSize(5);
}

void Bullet::Draw(SDL_Surface* screen, float fDeltaTime, float winX, float winY)
{
	SDL_Rect dclip;
	SDL_Surface* temp = NULL;
	temp = rotozoomSurface(GetSurface(), GetDirection(), 1.0, 0);
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 255, 0, 255));

	dclip.x = GetX() - (temp->w/2) - winX;
	dclip.y = GetY() - (temp->h/2) - winY;
	dclip.w = temp->w; dclip.h = temp->h;

	SDL_BlitSurface(temp, &temp->clip_rect, screen, &dclip);
	SDL_FreeSurface(temp);

	//rectangleRGBA(screen, GetX() - (GetSize() / 2), GetY() - (GetSize() / 2), GetX() + (GetSize() / 2), GetY() + (GetSize() / 2), 0, 0, 0, 255);
}
void Bullet::Update(float fDeltaTime)
{
	if (GetState() == stateAlive)
	{
		float tempX = 0, tempY = 0;
		tempX = GetX() - ((GetMoveSpeed() * fDeltaTime) * sin((GetDirection()) * M_PI / 180));
		tempY = GetY() - ((GetMoveSpeed() * fDeltaTime) * cos((GetDirection()) * M_PI / 180));
		SetX(tempX);
		SetY(tempY);

		//d = sqrt ((x2 - x1)2 + (y2 - y1)2)

		float fTempLife = 0; //GetLife();
		fTempLife = sqrtf( powf((GetX() - GetOX()), 2) + powf((GetY() - GetOY()), 2));
		
		SetLife(fTempLife);
		if (GetLife() >= GetMaxLife())
			{SetState(stateDead);}
	}
}
void Bullet::Collide(Object* obj)
{
	if (obj->GetType() == typeCharacter)
	{
		Character* c1 = dynamic_cast<Character*>(obj);
		if (c1->GetCharID() == GetOwner())
		{return;}
	}

	if (obj->GetType() != typePickup)
		{SetState(stateDead);}
}
void Bullet::Dispose()
{
	SDL_FreeSurface(GetSurface());
}

void Bullet::SetBullType(int bt)
{
	m_iBullType = bt;
}
void Bullet::SetOwner(int o)
{
	m_iOwner = o;
}
void Bullet::SetMoveSpeed(float ms)
{
	m_fMoveSpeed = ms;
}
void Bullet::SetDirection(float d)
{
	m_fDirection = d;
}
void Bullet::SetLife(float l)
{
	m_fLife = l;
}
void Bullet::SetMaxLife(int ml)
{
	m_iMaxLife = ml;
}
void Bullet::SetOX(float ox)
{
	m_fOX = ox;
}
void Bullet::SetOY(float oy)
{
	m_fOY = oy;
}

int Bullet::GetBullType()
{
	return m_iBullType;
}
int Bullet::GetOwner()
{
	return m_iOwner;
}
float Bullet::GetMoveSpeed()
{
	return m_fMoveSpeed;
}
float Bullet::GetDirection()
{
	return m_fDirection;
}
float Bullet::GetLife()
{
	return m_fLife;
}
int Bullet::GetMaxLife()
{
	return m_iMaxLife;
}
float Bullet::GetOX()
{
	return m_fOX;
}
float Bullet::GetOY()
{
	return m_fOY;
}

float Bullet::GetBulletDamage(int cID)
{
	float bd = 0;
	switch (cID)
	{
	case cidRaynos:
		bd = 1;
	break;
	case cidPteras:
		bd = 5;
	break;
	case cidBuster:
		bd = 40;
	break;
	case cidZabat:
		bd = 1;
	break;
	case cidRedler:
		bd = 5;
	break;
	case cidStorm:
		bd = 5;
	break;
	}
	return bd;
}
float Bullet::GetBulletSpeed(int cID)
{
	float bs = 0;
	switch (cID)
	{
	case cidRaynos:
		bs = 300;
	break;
	case cidPteras:
		bs = 500;
	break;
	case cidBuster:
		bs = 300;
	break;
	case cidZabat:
		bs = 400;
	break;
	case cidRedler:
		bs = 500;
	break;
	case cidStorm:
		bs = 500;
	break;
	}
	return bs;
}

int Bullet::GetBulletMaxLife(int cID)
{
	int ml = 0;
	switch (cID)
	{
	case cidRaynos:
		ml = 500;
	break;
	case cidPteras:
		ml = 500;
	break;
	case cidBuster:
		ml = 500;
	break;
	case cidZabat:
		ml = 500;
	break;
	case cidRedler:
		ml = 500;
	break;
	case cidStorm:
		ml = 500;
	break;
	}
	return ml;
}