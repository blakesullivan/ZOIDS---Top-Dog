//Blake Sullivan - FleeState.h
#ifndef FLEESTATE_H
#define FLEESTATE_H

#include "State.h"

class AI_FLEE: public State
{
private:
	bool m_bFoundWay;
public:
	AI_FLEE(Character* thepBot, Level *w, Object* pTar, PathFinder* pf);//, WayStar* ws);
	~AI_FLEE() {};

	void activate();
	void process(float fDeltaTime);
	void terminate();
	int getStatus();
	void setTarget(Object *Target);
};

#endif