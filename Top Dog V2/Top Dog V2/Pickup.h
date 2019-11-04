//Blake Sullivan - Pickup.h
#ifndef PICKUP_H
#define PICKUP_H

#include "Object.h"

class Pickup : public Object
{
private:
	int m_iPickupType;
	float m_fRespawnTimer;
	
public:
	Pickup();
	~Pickup() {};

	void Init(int pt, float x, float y);

	void Draw(SDL_Surface* screen, float fDeltaTime, float winX, float winY);
	void Update(float fDeltaTime);
	void Collide(Object* obj);
	void Dispose();

	void SetTypeDifferences(int pt);

	void SetPickupType(int pt);
	void SetRespawnTimer(float rt);
	int GetPickupType();
	float GetRespawnTimer();
};

#endif