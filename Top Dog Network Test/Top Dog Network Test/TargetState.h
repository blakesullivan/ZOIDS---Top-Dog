//Blake Sullivan - TargetState.h
#ifndef TARGETSTATE_H
#define TARGETSTATE_H

#include "State.h"

class AI_SEARCH_TARGET: public State
{
public:
	AI_SEARCH_TARGET(Character* thepBot, Level *w, Object* pTar);
	~AI_SEARCH_TARGET() {};

	void activate();
	void process();
	void terminate();
	int getStatus();
	void setTarget(Object *Target);

};

#endif