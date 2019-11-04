//Blake Sullivan - Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"
#include "CharStats.h"
//#include "FSM.h"
#include <string>
using namespace std;

class Character : public Object
{
private:
	//FSM* m_pFSM;
	//Level* m_pLevel;
	int m_iCharID;
	string m_sName;
	bool m_bInGame;
	bool m_bIsBot;
	CharStats m_cStats;
	string m_sSurfaceName;
	float m_fRespawnTimer;
	bool m_bUsingEnergy;
	bool m_bMoved;
	bool m_bFired;

public:
	Character();
	~Character() {};

	void Init(int cID, float x, float y, string name, bool bot);
	void LoadCharDiff(int cID);

	void Draw(SDL_Surface* screen, float fDeltaTime, float winX, float winY);
	void Update(float fDeltaTime);
	void Collide(Object* obj);
	void Dispose();

	void MoveCharacter(char cDir, float fdt);
	void MoveLeft(float fdt, float speedMult);
	void MoveRight(float fdt, float speedMult);
	void MoveUp(float fdt, float speedMult);
	void MoveDown(float fdt, float speedMult);
	void RotateLeft(float fdt, float speedMult);
	void RotateRight(float fdt, float speedMult);

	void SetCharID(int);
	void SetName(string);
	void SetInGame(bool);
	void SetIsBot(bool);
	void SetSurfaceName(string);
	void SetRespawnTimer(float rt);
	void SetIsUsingEnergy(bool ue);
	void SetFired(bool f);

	int GetCharID();
	string GetName();
	CharStats* GetStats();
	bool GetInGame();
	bool GetIsBot();
	string GetSurfaceName();
	float GetRespawnTimer();
	bool GetIsUsingEnergy();
	bool GetFired();
};

#endif