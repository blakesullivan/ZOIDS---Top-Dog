//Blake Sullivan - FightState.cpp
#include "FightState.h"
#include "Level.h"
//#include "WayStar.h"

AI_FIGHT::AI_FIGHT(Character* thepBot, Level *w, Object* pTar, PathFinder* pf)//, WayStar* ws)
{
	theworld = w;
	mOwner = thepBot;
	target = pTar;
	m_pPF = pf;
}
void AI_FIGHT::activate()
{
	status = stateAlive;
}
void AI_FIGHT::process(float fDeltaTime)
{
	if (target == NULL) {return;}
	float fTempDeg = 0;
	fTempDeg = atan( (target->GetX() - mOwner->GetX()) / (target->GetY() - mOwner->GetY()) ) * 180 / M_PI;
	//fTempDeg += 90;
	if (target->GetY() > mOwner->GetY()) {fTempDeg += 180;}

	/*if (mOwner->GetCharID() == cidPteras)
	{
		cout << "fTempDeg: " << fTempDeg << " PlayerDeg: " << mOwner->GetStats()->GetDirection() << endl;
	}*/

	if (mOwner->GetStats()->GetDirection() < fTempDeg - 5)
		{mOwner->RotateLeft(fDeltaTime, 1);}
	else if (mOwner->GetStats()->GetDirection() > fTempDeg + 5)
		{mOwner->RotateRight(fDeltaTime, 1);}
	else
		{mOwner->GetStats()->SetDirection(fTempDeg);}

	fShootTime -= fDeltaTime;
	if (mOwner->GetStats()->GetDirection() == fTempDeg && fShootTime <= 0)
	{
		theworld->AddBullet(mOwner->GetCharID(), false);
		fShootTime = mOwner->GetStats()->GetRateOfFire();
	}
}
void AI_FIGHT::terminate()
{
}
int AI_FIGHT::getStatus()
{
	return status;
}
void AI_FIGHT::setTarget(Object *Target)
{
	target = Target;
}