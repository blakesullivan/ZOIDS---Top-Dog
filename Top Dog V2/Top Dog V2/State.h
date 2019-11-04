//Blake Sullivan - State.h
#ifndef STATE_H
#define STATE_H

#include "Level.h"
#include "Character.h"

namespace GameFlowType
{
	const int AI_SEARCH_H = 0;
	const int AI_SEARCH_A = 1;
	const int AI_SEARCH_E = 2;
	const int AI_FIGHT = 3;
	const int AI_FLEE = 4;
	const int HEALTH = 0;
	const int AMMO = 1;
	const int ENEMY = 2;
};

class State
{
protected:
	int id;				//each goal has an id
	Level* theworld;	// a pointer to the world
	Character *mOwner;	// a pointer to the player
	Object *target;  // the target object
	int status;
	int type;
public:
	//STATE();
	State() {};
	~State() {};
	virtual void activate()=0;
	virtual void process()=0;
	virtual void terminate()=0;
	virtual int getStatus()=0;
	virtual void setTarget(Object *Target)=0;
};
#endif