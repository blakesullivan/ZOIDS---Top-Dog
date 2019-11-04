//Blake Sullivan - Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"
#include "CharStats.h"
#include <string>
using namespace std;

class Character : public Object
{
private:
	int m_iCharID;
	string m_sName;
	bool m_bInGame;
	bool m_bIsBot;
	CharStats m_cStats;
	string m_sSurfaceName;
	float m_fRespawnTimer;

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
	void MoveLeft(float fdt, int speedMult);
	void MoveRight(float fdt, int speedMult);
	void MoveUp(float fdt, int speedMult);
	void MoveDown(float fdt, int speedMult);
	void RotateLeft(float fdt, int speedMult);
	void RotateRight(float fdt, int speedMult);

	void SetCharID(int);
	void SetName(string);
	void SetInGame(bool);
	void SetIsBot(bool);
	void SetSurfaceName(string);
	void SetRespawnTimer(float rt);

	int GetCharID();
	string GetName();
	CharStats* GetStats();
	bool GetInGame();
	bool GetIsBot();
	string GetSurfaceName();
	float GetRespawnTimer();
};

#endif