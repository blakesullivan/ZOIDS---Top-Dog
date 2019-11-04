//Blake Sullivan - Bullet.h
#ifndef BULLET_H
#define BULLET_H

#include "Object.h"
#include "CharHeader.h"

class Bullet : public Object
{
private:
	int m_iBullType;
	int m_iOwner;
	float m_fMoveSpeed;
	float m_fDirection;
	float m_fLife;
	int m_iMaxLife;
	float m_fOX, m_fOY;

public:
	Bullet();
	~Bullet() {};

	void Init(int o, int bt, float x, float y, float dir);

	void Draw(SDL_Surface* screen, float fDeltaTime, float winX, float winY);
	void Update(float fDeltaTime);
	void Collide(Object* obj);
	void Dispose();

	void SetBullType(int);
	void SetOwner(int);
	void SetMoveSpeed(float);
	void SetDirection(float);
	void SetLife(float);
	void SetMaxLife(int);
	void SetOX(float);
	void SetOY(float);

	int GetBullType();
	int GetOwner();
	float GetMoveSpeed();
	float GetDirection();
	float GetLife();
	int GetMaxLife();
	float GetOX();
	float GetOY();

	float GetBulletDamage(int cID);
	float GetBulletSpeed(int cID);
	int GetBulletMaxLife(int cID);
};

#endif