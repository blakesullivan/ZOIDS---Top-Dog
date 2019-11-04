//Blake Sullivan - FSM.cpp
#include "FSM.h"

void FSM::init()
{
	AI_SEARCH_TARGET *b = new AI_SEARCH_TARGET(pBot, theworld, pTarget);
	aistates.push_back( b );
	AI_FIGHT *b1 = new AI_FIGHT(pBot, theworld, pTarget);
	aistates.push_back( b1 );
	AI_FLEE *b2 = new AI_FLEE(pBot, theworld, pTarget);
	aistates.push_back( b2 );

	AIstate=GameFlowType::AI_SEARCH_E;
}


void  FSM::process()
{
	//…
	//… some code here to do the targeting

	bool LOS = false;

	int oldstate = AIstate;
	if ( pBot->GetStats()->GetBulletsLeft() >=20 && pBot->GetStats()->GetHealth() >=20 && LOS==true )
		AIstate=GameFlowType::AI_FIGHT;
	else if  ( pBot->GetStats()->GetHealth() < 50 && LOS==false)
		AIstate=GameFlowType::AI_SEARCH_H;
	else if  ( pBot->GetStats()->GetBulletsLeft() < 50 && LOS==false)
		AIstate=GameFlowType::AI_SEARCH_A;
	else if  ( pBot->GetStats()->GetBulletsLeft() >=50 && pBot->GetStats()->GetHealth() >=50 && LOS==false)
		AIstate=GameFlowType::AI_SEARCH_E;
	else if  ( (pBot->GetStats()->GetBulletsLeft() <20 || pBot->GetStats()->GetHealth() <20) && LOS==true)
		AIstate=GameFlowType::AI_FLEE;
	else {
		cout << "NOOOOOOOOOOOOO!!!"<< endl;
	}

	int d = 0;

	if (oldstate != AIstate)
	{
		aistates[oldstate%3]->terminate(); // if you really need to do this
		switch (AIstate)
		{
		case GameFlowType::AI_SEARCH_H:
			pTarget=theworld->FindNearestObject(pBot->GetX(),pBot->GetY(), GameFlowType::HEALTH, pBot->GetID(), d);
			aistates[AIstate%3]->setTarget(pTarget);
			aistates[AIstate%3]->activate();
			cout << "SEARCH FOR HEALTH"  << pTarget->GetID() << endl;
			break;
		case GameFlowType::AI_SEARCH_A:
			pTarget=theworld->FindNearestObject(pBot->GetX(),pBot->GetY(), GameFlowType::AMMO, pBot->GetID(), d);
			aistates[AIstate%3]->setTarget(pTarget);
			aistates[AIstate%3]->activate();
			cout << "SEARCH FOR AMMO"  << pTarget->GetID() << endl;
			break;
		case GameFlowType::AI_SEARCH_E:
			aistates[AIstate%3]->setTarget(pTarget2);
			aistates[AIstate%3]->activate();
			cout << "SEARCH FOR ENEMY"  << pTarget2->GetID() << endl;
			break;
		case GameFlowType::AI_FIGHT:
			aistates[AIstate%3]->setTarget(pTarget2); // just set it any way just in case we change targets?? did we handle that above
			aistates[AIstate%3]->activate();
			cout << "FIGHT"  << pTarget2->GetID() << endl;
			break;
		case GameFlowType::AI_FLEE:
			pTarget=theworld->FindFurtherestObject(pBot->GetX(),pBot->GetY(), pBot->GetID());
			aistates[AIstate%3]->setTarget(pTarget);
			aistates[AIstate%3]->activate(); //this sets the target x and Y
			cout << "FLEE"  << pTarget->GetID() << endl;
			break;

	// all this code assumes the target was found and there is a valid point er here
			// ie i dont do any error checking


		}

	}

	// process whatever is the selected state
	aistates[AIstate%3]->process();

}

//---------------------------------------------------------------------------------

//In the player init()
//		brain = new FSM	(this, theworld);

//in the player update function ()
//	brain->process();
