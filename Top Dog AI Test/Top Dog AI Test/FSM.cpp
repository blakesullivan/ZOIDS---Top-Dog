//Blake Sullivan - FSM.cpp
#include "FSM.h"
#include "Level.h"

FSM::FSM(Character *PBOT, Level *w, PathFinder* pf)
{
	theworld = w;
	pBot = PBOT;
	m_pPF = pf;
	//m_pWS = new WayStar();
	//m_pWS->Init(theworld->GetMap()->GetWidth() / 32, theworld->GetMap()->GetHeight() / 32);
	//m_pWS->LoadData(theworld->GetMap()->GetWayStarData().c_str());
	init();
}
FSM::~FSM()
{
	aistates.clear();
}

void FSM::init()
{
	AI_SEARCH_TARGET *b = new AI_SEARCH_TARGET(pBot, theworld, pTarget, m_pPF);//, m_pWS);
	aistates.push_back(b);
	/*AI_SEARCH_TARGET *b1 = new AI_SEARCH_TARGET(pBot, theworld, pTarget, m_pPF);//, m_pWS);
	aistates.push_back(b1);
	AI_SEARCH_TARGET *b2 = new AI_SEARCH_TARGET(pBot, theworld, pTarget, m_pPF);//, m_pWS);
	aistates.push_back(b2);
	AI_SEARCH_TARGET *b3 = new AI_SEARCH_TARGET(pBot, theworld, pTarget, m_pPF);//, m_pWS);
	aistates.push_back(b3);*/
	AI_FIGHT *b4 = new AI_FIGHT(pBot, theworld, pTarget, m_pPF);//, m_pWS);
	aistates.push_back(b4);
	AI_FLEE *b5 = new AI_FLEE(pBot, theworld, pTarget, m_pPF);//, m_pWS);
	aistates.push_back(b5);

	AIstate = GameFlowType::AI_FIGHT;

	pTarget = NULL;
	pTarget2 = NULL;
}


void  FSM::process(float fDeltaTime)
{
	//…
	//… some code here to do the targeting

	bool LOS = false;
	bool bChangeTarget = false;

	if (pTarget != NULL)
	{
		if (pTarget->GetState() != stateAlive)
			{bChangeTarget = true;}
		else
			{LOS = FindLineOfSight();}
	}

	int oldstate = AIstate;
	if (pBot->GetStats()->GetBulletsLeft() > 20 && pBot->GetStats()->GetHealth() > 30 && LOS == true)
		{AIstate = GameFlowType::AI_FIGHT;}
	else if (pBot->GetStats()->GetHealth() < 50 && LOS == false)
		{AIstate=GameFlowType::AI_HEALTH;}
	else if (pBot->GetStats()->GetBulletsLeft() < 50 && LOS == false)
		{AIstate=GameFlowType::AI_AMMO;}
	else if (pBot->GetStats()->GetEnergy() == 0 && LOS == false)
		{AIstate=GameFlowType::AI_ENERGY;}
	else if (pBot->GetStats()->GetBulletsLeft() >= 50 && pBot->GetStats()->GetHealth() >= 50 && LOS == false)
		{AIstate=GameFlowType::AI_OPPONENT;}
	else if ((pBot->GetStats()->GetBulletsLeft() < 20 || pBot->GetStats()->GetHealth() < 30) && LOS == true)
		{AIstate=GameFlowType::AI_FLEE;}
	else 
	{
		//AIstate=GameFlowType::AI_OPPONENT;
		cout << pBot->GetCharID() << " NOOOOOOOOOOOOO!!!"<< endl;
	}

	

	int d = -1;

	if (oldstate != AIstate || bChangeTarget == true)
	{
		//cout << "FSM change for: " << pBot->GetCharID() << endl;
		if (oldstate != -1) {aistates[oldstate%3]->terminate();} // if you really need to do this
		switch (AIstate)
		{
		case GameFlowType::AI_HEALTH:
			pTarget = theworld->FindNearestObject(pBot->GetX(),pBot->GetY(), pBot->GetID(), GameFlowType::AI_SEARCH_H, d);
			if (pTarget == NULL) {AIstate = -1; return;}
			aistates[0]->setTarget(pTarget);
			aistates[0]->activate();
			//cout << "SEARCH FOR HEALTH"  << pTarget->GetID() << endl;
		break;
		case GameFlowType::AI_AMMO:
			pTarget = theworld->FindNearestObject(pBot->GetX(),pBot->GetY(), pBot->GetID(), GameFlowType::AI_SEARCH_A, d);
			if (pTarget == NULL) {AIstate = -1; return;}
			aistates[0]->setTarget(pTarget);
			aistates[0]->activate();
			//cout << "SEARCH FOR AMMO"  << pTarget->GetID() << endl;
		break;
		case GameFlowType::AI_ENERGY:
			pTarget = theworld->FindNearestObject(pBot->GetX(),pBot->GetY(), pBot->GetID(), GameFlowType::AI_SEARCH_E, d);
			if (pTarget == NULL) {AIstate = -1; return;}
			aistates[0]->setTarget(pTarget);
			aistates[0]->activate();
			//cout << "SEARCH FOR ENERGY"  << pTarget->GetID() << endl;
		break;
		case GameFlowType::AI_OPPONENT:
			pTarget = theworld->FindNearestObject(pBot->GetX(),pBot->GetY(), pBot->GetID(), GameFlowType::AI_SEARCH_O, d);
			if (pTarget == NULL) {AIstate = -1; return;}
			aistates[0]->setTarget(pTarget);
			aistates[0]->activate();
			//cout << "SEARCH FOR OPPONENT"  << pTarget->GetID() << endl;
		break;
		case GameFlowType::AI_FIGHT:
			aistates[1]->setTarget(pTarget); // just set it any way just in case we change targets?? did we handle that above
			aistates[1]->activate();
			cout << "FIGHT"  << pTarget->GetID() << endl;
		break;
		case GameFlowType::AI_FLEE:
			pTarget = theworld->FindFurthestObject(pBot->GetX(),pBot->GetY(), pBot->GetID());
			if (pTarget == NULL) {AIstate = -1; return;}
			aistates[2]->setTarget(pTarget);
			aistates[2]->activate(); //this sets the target x and Y
			//cout << "FLEE"  << pTarget->GetID() << endl;
		break;

			// all this code assumes the target was found and there is a valid pointer here
			// ie i dont do any error checking


		}

	}

	if (pBot->GetState() == stateAlive)
	{
		//cout << "FSM: " << pBot->GetCharID() << endl;
		// process whatever is the selected state
		aistates[AIstate%3]->process(fDeltaTime);
	}

}

bool FSM::FindLineOfSight()
{
	bool LOS = false;
	if (pTarget->GetType() == typeCharacter)
	{
		float fDistance = 0, fRadius = pow(300.0, 2.0);
		fDistance = pow((pTarget->GetX() - pBot->GetX()), 2)+ pow((pTarget->GetY() - pBot->GetY()), 2);
		if (fDistance <= fRadius)
		{
			LOS = true;
		}

		/*if (pBot->GetCharID() == cidRedler)
		{
			cout << "LOS: " << LOS << " fDistance: " << fDistance << " fRadius: " << fRadius << endl;
		}*/
	}
	return LOS;
}

/*WayStar* FSM::GetWS()
{
	return m_pWS;
}*/

//---------------------------------------------------------------------------------

//In the player init()
//		brain = new FSM	(this, theworld);

//in the player update function ()
//	brain->process();
