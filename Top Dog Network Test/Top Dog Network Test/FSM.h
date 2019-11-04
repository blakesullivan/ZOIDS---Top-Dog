//Blake Sullivan - FSM.h
#ifndef FSM_H
#define FSM_H

#include "TargetState.h"
#include "FightState.h"
#include "FleeState.h"
#include <vector>
using namespace std;

class FSM
{
private:
	Level * theworld;
	Character *pBot;
	Object *pTarget;
	Object* pTarget2;
	vector<State*> aistates;
	int AIstate;

public:
	FSM(Character* PBOT, Level *w);
	~FSM();

	void process();
	void init();
	void dispose();
};
#endif