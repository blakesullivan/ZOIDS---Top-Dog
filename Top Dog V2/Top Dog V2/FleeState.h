//Blake Sullivan - FleeState.h
#ifndef FLEESTATE_H
#define FLEESTATE_H

#include "State.h"

class AI_FLEE: public State
{
public:
	AI_FLEE(Character* thepBot, Level *w, Object* pTar);
	~AI_FLEE() {};

	void activate();
	void process();
	void terminate();
	int getStatus();
	void setTarget(Object *Target);
};

#endif