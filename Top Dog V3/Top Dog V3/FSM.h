//Blake Sullivan - FSM.h
#ifndef FSM_H
#define FSM_H

//class Level;
#include "TargetState.h"
#include "FightState.h"
#include "FleeState.h"
#include <vector>
using namespace std;

class FSM
{
private:
	Level *theworld;
	Character *pBot;
	Object *pTarget;
	Object* pTarget2;
	PathFinder* m_pPF;
	//WayStar* m_pWS;
	vector<State*> aistates;
	int AIstate;

public:
	FSM(Character* PBOT, Level *w, PathFinder* pf);
	~FSM();

	void init();
	void process(float fDeltaTime);
	void dispose();

	bool FindLineOfSight();

	//WayStar* GetWS();
};
#endif