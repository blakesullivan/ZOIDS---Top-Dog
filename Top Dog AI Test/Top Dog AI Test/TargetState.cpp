//Blake Sullivan - TargetState.cpp
#include "TargetState.h"
#include "Level.h"
//#include "WayStar.h"

AI_SEARCH_TARGET::AI_SEARCH_TARGET(Character* thepBot, Level *w, Object* pTar, PathFinder* pf)//, WayStar* ws)
{
	theworld = w;
	mOwner = thepBot;
	target = pTar;
	m_pPF = pf;
	//m_pWS = ws;
	m_bFoundWay = false;
	m_fNextX = 0; m_fNextY = 0;
	m_fLastTargX = 0; m_fLastTargY = 0;
}

void AI_SEARCH_TARGET::activate()
{
	status = stateAlive;
	m_bFoundWay = false;
}

void AI_SEARCH_TARGET::process(float fDeltaTime)
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
		{tempDeg = 0;}
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

	if (mOwner->GetCharID() == cidRedler)
	{
		//cout << "TempDeg: " << tempDeg << " PlayerDeg: " << mOwner->GetStats()->GetDirection() << endl;
	}
	
	if ((mOwner->GetStats()->GetDirection() < tempDeg - 10 || mOwner->GetStats()->GetDirection() > tempDeg + 10) && tempDeg > -1)
	{
		if (mOwner->GetStats()->GetDirection() < tempDeg)
			{mOwner->RotateLeft(fDeltaTime, 1);}
		else if (mOwner->GetStats()->GetDirection() > tempDeg)
			{mOwner->RotateRight(fDeltaTime, 1);}

		/*if (tempDeg > 0 && tempDeg <= 180)
			{mOwner->RotateLeft(fDeltaTime, 1);}
		else if (tempDeg > 180 && tempDeg < 360)
			{mOwner->RotateRight(fDeltaTime, 1);}*/
	}
	else
	{
		
		if (CurrX == MoveX && CurrY == MoveY)
		{
			//cout << "Should be Making it Go Through again.\n";
			//system("PAUSE");
			m_bFoundWay = false;
			mOwner->SetX(m_fNextX);
			mOwner->SetY(m_fNextY);
		}
		//else
		{mOwner->MoveCharacter('u', fDeltaTime);}
	}

	
	//mOwner->SetX((MoveX * 32) + (16));} // + (Square::GetSize() / 2));
	//mOwner->SetY((MoveY * 32) + (16));} // + (Square::GetSize() / 2));

	
	/*if (m_bFoundWay == false)
	{
		m_pWS->Manager(mOwner->GetX()/32, mOwner->GetY()/32, target->GetX()/32, target->GetY()/32);
		m_bFoundWay = true;
	}
	int nodeX = m_pWS->getNextX(), nodeY = m_pWS->getNextY();
	float tempDeg = atan((nodeX - mOwner->GetX()) / (nodeY - mOwner->GetY())) * 180 / M_PI;
	tempDeg += 90;
	if (nodeY > mOwner->GetY()) {tempDeg += 180;}

	//cout << "tempDeg: " << tempDeg;
	//tempDeg = (tempDeg * M_PI / 180);
	if (mOwner->GetCharID() == cidZabat)
	{
		cout << "Before Movement: ";
		cout << "mOwner->GetStats()->GetDirection(): " << mOwner->GetStats()->GetDirection();
		cout << "tempDeg: " << tempDeg << endl;
		cout << "Player Pos: x: " << mOwner->GetX() << " y: " << mOwner->GetY();
		cout << " Node Pos: x: " << nodeX << " y: " << nodeY << endl;;
	}
	
	//mOwner->GetStats()->SetDirection(tempDeg);
	
	if (tempDeg > mOwner->GetStats()->GetDirection())
		{mOwner->RotateRight(fDeltaTime, 1);}
	else if (tempDeg < mOwner->GetStats()->GetDirection())
		{mOwner->RotateLeft(fDeltaTime, 1);}
	
	if ((mOwner->GetStats()->GetDirection()-5) > tempDeg || (mOwner->GetStats()->GetDirection()+5) < tempDeg)
	{
		mOwner->MoveCharacter('u', fDeltaTime);
	}
	
	if (theworld->CheckCollision(mOwner->GetX() - 16, mOwner->GetY() - 16, 32, nodeX, nodeY, 32) == true)
		{m_pWS->NextNode();}

	if (mOwner->GetCharID() == cidZabat)
	{
		cout << "After Movement: ";
		cout << "mOwner->GetStats()->GetDirection(): " << mOwner->GetStats()->GetDirection();
		cout << "tempDeg: " << tempDeg << endl;
		cout << "Player Pos: x: " << mOwner->GetX() << " y: " << mOwner->GetY();
		cout << " Node Pos: x: " << nodeX << " y: " << nodeY << endl;
	}
	
	//int nextX = m_pWS->getNextX() + mOwner->GetX();
	//int nextY = m_pWS->getNextY() + mOwner->GetY();
	//if (nextX == m_pWS->NextNode()
	//mOwner->SetX(nextX);
	//mOwner->SetY(nextY);
	*/
}

void AI_SEARCH_TARGET::terminate()
{
	status = stateDead;
	m_bFoundWay = false;
}

int AI_SEARCH_TARGET::getStatus()
{
	return 0;
}

void AI_SEARCH_TARGET::setTarget(Object *Target)
{
	target = Target;
}