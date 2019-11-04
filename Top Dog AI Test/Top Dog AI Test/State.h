//Blake Sullivan - State.h
#ifndef STATE_H
#define STATE_H

class Level;
#include "Character.h"
//class Object;
#include "PathFinder.h"
#include "StateHeader.h"

class State
{
protected:
	int id;				//each goal has an id
	Level* theworld;	// a pointer to the world
	Character *mOwner;	// a pointer to the player
	Object *target;  // the target object
	PathFinder* m_pPF;
	//WayStar* m_pWS;
	int status;
	int type;
	float m_fNextX, m_fNextY;
	float m_fLastTargX, m_fLastTargY;
public:
	//STATE();
	State() {};
	~State() {};
	virtual void activate()=0;
	virtual void process(float fDeltaTime)=0;
	virtual void terminate()=0;
	virtual int getStatus()=0;
	virtual void setTarget(Object *Target)=0;
};
#endif