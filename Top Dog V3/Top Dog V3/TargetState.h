//Blake Sullivan - TargetState.h
#ifndef TARGETSTATE_H
#define TARGETSTATE_H

#include "State.h"

class AI_SEARCH_TARGET: public State
{
private:
	bool m_bFoundWay;
public:
	AI_SEARCH_TARGET(Character* thepBot, Level *w, Object* pTar, PathFinder* pf);
	~AI_SEARCH_TARGET() {};

	void activate();
	void process(float fDeltaTime);
	void terminate();
	int getStatus();
	void setTarget(Object *Target);

};

#endif