//Blake Sullivan - CharStats.cpp
#include "CharStats.h"

CharStats::CharStats()
{
	SetMaxHealth(0);
	SetMaxEnergy(0);
	SetHealth(0);
	SetEnergy(0);
	SetMoveSpeed(0);
	SetRateOfFire(0);
	SetChangeAngle(0);
	SetDirection(0);
	SetRotateAngle(0);
	SetBulletType(0);
	SetBulletMax(0);
	SetBulletsLeft(0);
}

void CharStats::SetMaxHealth(float mh)
{
	m_fMaxHealth = mh;
	SetHealth(mh);
}
void CharStats::SetMaxEnergy(float me)
{
	m_fMaxEnergy = me;
	SetEnergy(me);
}
void CharStats::SetHealth(float h)
{
	m_fHealth = h;
}
void CharStats::SetEnergy(float e)
{
	m_fEnergy = e;
}
void CharStats::SetMoveSpeed(float ms)
{
	m_fMoveSpeed = ms;
}
void CharStats::SetRateOfFire(float rof)
{
	m_fRateOfFire = rof;
}
void CharStats::SetChangeAngle(float ca)
{
	m_fChangeAngle = ca;
}
void CharStats::SetDirection(float d)
{
	m_fDirection = d;
}
void CharStats::SetRotateAngle(float ra)
{
	m_fRotateAngle = ra;
}
void CharStats::SetBulletType(int bt)
{
	m_iBulletType = bt;
}
void CharStats::SetBulletMax(int bm)
{
	m_iBulletMax = bm;
	SetBulletsLeft(bm);
}
void CharStats::SetBulletsLeft(int bl)
{
	m_iBulletsLeft = bl;
}

float CharStats::GetHealth()
{
	return m_fHealth;
}
float CharStats::GetEnergy()
{
	return m_fEnergy;
}
float CharStats::GetMaxHealth()
{
	return m_fMaxHealth;
}
float CharStats::GetMaxEnergy()
{
	return m_fMaxEnergy;
}
float CharStats::GetMoveSpeed()
{
	return m_fMoveSpeed;
}
float CharStats::GetRateOfFire()
{
	return m_fRateOfFire;
}
float CharStats::GetChangeAngle()
{
	return m_fChangeAngle;
}
float CharStats::GetDirection()
{
	return m_fDirection;
}
float CharStats::GetRotateAngle()
{
	return m_fRotateAngle;
}

int CharStats::GetBulletType()
{
	return m_iBulletType;
}
float CharStats::GetBulletMax()
{
	return m_iBulletMax;
}
float CharStats::GetBulletsLeft()
{
	return m_iBulletsLeft;
}