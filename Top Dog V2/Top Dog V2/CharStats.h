//Blake Sullivan - CharStats.h
#ifndef CHARSTATS_H
#define CHARSTATS_H

#include "CharHeader.h"
class CharStats
{
private:
	float m_fHealth, m_fEnergy;
	float m_fMaxHealth, m_fMaxEnergy;
	float m_fMoveSpeed, m_fRateOfFire;
	float m_fChangeAngle, m_fDirection, m_fRotateAngle;
	int m_iBulletType, m_iBulletMax, m_iBulletsLeft;

public:
	CharStats();
	~CharStats() {};

	void SetMaxHealth(float mh);
	void SetMaxEnergy(float me);
	void SetHealth(float h);
	void SetEnergy(float e);
	void SetSpecial(float s);
	void SetMoveSpeed(float ms);
	void SetRateOfFire(float rof);
	void SetChangeAngle(float ca);
	void SetDirection(float d);
	void SetRotateAngle(float ra);
	void SetBulletType(int bt);
	void SetBulletMax(int bm);
	void SetBulletsLeft(int bl);

	float GetHealth();
	float GetEnergy();
	float GetMaxHealth();
	float GetMaxEnergy();
	float GetMoveSpeed();
	float GetRateOfFire();
	float GetChangeAngle();
	float GetDirection();
	float GetRotateAngle();
	int GetBulletType();
	int GetBulletMax();
	int GetBulletsLeft();
};
#endif