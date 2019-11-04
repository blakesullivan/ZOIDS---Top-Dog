//Blake Sullivan - FightState.h
#ifndef FIGHTSTATE_H
#define FIGHTSTATE_H

#include "State.h"

class AI_FIGHT: public State
{
public:
	AI_FIGHT(Character* thepBot, Level *w, Object* pTar);
	~AI_FIGHT() {};
	void activate();
	void process();
	void terminate();
	int getStatus();
	void setTarget(Object *Target);
};

#endif