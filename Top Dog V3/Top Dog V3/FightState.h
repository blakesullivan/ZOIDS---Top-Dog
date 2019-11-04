//Blake Sullivan - FightState.h
#ifndef FIGHTSTATE_H
#define FIGHTSTATE_H

#include "State.h"

class AI_FIGHT: public State
{
private:
	float fShootTime;
public:
	AI_FIGHT(Character* thepBot, Level *w, Object* pTar, PathFinder* pf);//, WayStar* ws);
	~AI_FIGHT() {};
	void activate();
	void process(float fDeltaTime);
	void terminate();
	int getStatus();
	void setTarget(Object *Target);
};

#endif