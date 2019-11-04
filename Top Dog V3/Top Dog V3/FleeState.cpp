//Blake Sullivan - FleeState.cpp
#include "FleeState.h"
#include "Level.h"
//#include "WayStar.h"

AI_FLEE::AI_FLEE(Character* thepBot, Level *w, Object* pTar, PathFinder* pf)//, WayStar* ws)
{
	theworld = w;
	mOwner = thepBot;
	target = pTar;
	m_pPF = pf;
}
void AI_FLEE::activate()
{
	status = stateAlive;
}
void AI_FLEE::process(float fDeltaTime)
{
	int MoveX = 0, MoveY = 0;
	int CurrX = mOwner->GetX()/32, CurrY = mOwner->GetY()/32;
	int TargX = target->GetX()/32, TargY = target->GetY()/32;

	if (m_fLastTargX != target->GetX() || m_fLastTargY != target->GetY())
	{m_bFoundWay = false;}

	if (m_bFoundWay == false)
	{
		m_fLastTargX = target->GetX(); m_fLastTargY = target->GetY();
		m_pPF->findPath(CurrX, CurrY, TargX, TargY, MoveX, MoveY, false);
		m_bFoundWay = true;
	}
	else
	{
		MoveX = (m_fNextX-16) / 32;
		MoveY = (m_fNextY-16) / 32;
	}

	if (mOwner->GetCharID() == cidRedler)
	{
		//cout << "MoveX: " << MoveX << " MoveY: " << MoveY << " CurrX: " << CurrX << " CurrY: " << CurrY << "TargX: " << TargX << " TargY: " << TargY << endl;
	}

	//if (MoveX > 0 || ((int)(mOwner->GetX()/32) != (int)(target->GetX()/32)))
	{m_fNextX = (MoveX * 32) + 16;}
	
	//if (MoveY > 0 || ((int)(mOwner->GetY()/32) != (int)(target->GetY()/32))) 
	{m_fNextY = (MoveY * 32) + 16;}

	float tempDeg = 0;
	
	if (MoveX == CurrX && MoveY == CurrY - 1)
	{
		if (mOwner->GetStats()->GetDirection() <= 180)
		{tempDeg = 0;}
		else if (mOwner->GetStats()->GetDirection() > 180)
		{tempDeg = 360;}
	}
	else if (MoveX == CurrX - 1 && MoveY == CurrY - 1)
		{tempDeg = 45;}
	else if (MoveX == CurrX - 1 && MoveY == CurrY)
		{tempDeg = 90;}
	else if (MoveX == CurrX - 1 && MoveY == CurrY + 1)
		{tempDeg = 135;}
	else if (MoveX == CurrX && MoveY == CurrY + 1)
		{tempDeg = 180;}
	else if (MoveX == CurrX + 1 && MoveY == CurrY + 1)
		{tempDeg = 225;}
	else if (MoveX == CurrX + 1 && MoveY == CurrY)
		{tempDeg = 270;}
	else if (MoveX == CurrX + 1 && MoveY == CurrY - 1)
		{tempDeg = 315;}
	else if (MoveX == CurrX && MoveY == CurrY)
		{tempDeg = -1;}
	
	if ((mOwner->GetStats()->GetDirection() < tempDeg - 10 || mOwner->GetStats()->GetDirection() > tempDeg + 10) && tempDeg > -1)
	{
		if (mOwner->GetStats()->GetDirection() < tempDeg)
			{mOwner->RotateLeft(fDeltaTime, 1);}
		else if (mOwner->GetStats()->GetDirection() > tempDeg)
			{mOwner->RotateRight(fDeltaTime, 1);}
	}
	else
	{
		if (tempDeg > -1) {mOwner->GetStats()->SetDirection(tempDeg);}

		if (CurrX == MoveX && CurrY == MoveY)
		{
			m_bFoundWay = false;
			mOwner->SetX(m_fNextX);
			mOwner->SetY(m_fNextY);
		}
		//else
		if (mOwner->GetCharID() == cidRaynos && mOwner->GetIsUsingEnergy() == false)
			{theworld->StartEnergy(mOwner->GetCharID());}

		{mOwner->MoveCharacter('u', fDeltaTime);}
	}
}
void AI_FLEE::terminate()
{
	status = stateDead;
	m_bFoundWay = false;
}
int AI_FLEE::getStatus()
{
	return 0;
}
void AI_FLEE::setTarget(Object *Target)
{
	target = Target;
}