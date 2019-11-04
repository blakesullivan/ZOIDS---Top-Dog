//Blake Sullivan - Level.h
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Character.h"
#include "Bullet.h"
#include "Pickup.h"
#include "Map.h"
#include "Explosions.h"
#include "SoundManager.h"
#include "FSM.h"
using std::vector;

class Level
{
private:
	SoundManager* m_pSM;
	vector<Object*> m_vpObj;
	vector<Object*>::iterator m_vpObjIT;
	//WayStar* m_pWS;
	FSM* m_aFSM[6];
	Map* m_pMap;
	float m_fWinPosX, m_fWinPosY;
	SDL_Surface* m_Arrow;
	PathFinder* m_pPF;
	bool m_bIsHost;
	int m_iMyID;

public:
	Level(SoundManager* sm);
	~Level();
	
	void Init(int myID, bool isHost);
	void Update(float fDeltaTime);
	void Draw(SDL_Surface* screen, float fDT);

	void AddCharacter(int cID, float x, float y, string name, int state, bool bot);
	void AddCharacter(int cID, string name, bool bot);	
	Character* GetCharacter(int id);
	void DrawZabatRadar(SDL_Surface* screen, float fDT);
	void SetSpawnPosition(int cID);
	
	void AddBullet(int cID, bool bUseAlt = false);
	void AddExplosion(Object* obj);
	void KillBullet(Object* obj, int pos);
	
	void AddPickup(int pt, float x, float y);
	void AddPickup(int pt);
	
	void CheckForCollisions();
	bool CheckCollision(Object* Obj1, Object* Obj2);
	bool CheckCollision(float p1X, float p1Y, float p1S, float p2X, float p2Y, float p2S);
	void CheckCollisionAgainst(Object* testObj);
	void CheckCollisionAgainstPos(int x, int y);
	
	Object* GetObject(int id);
	Object* FindNearestObject(int myX, int myY, int myID, int searchType = -1, float searchRadius = -1);
	Object* FindFurthestObject(int myX, int myY,int myID, int searchType = -1);
	
	void UpdateWindowPos(float, float);
	
	void StartEnergy(int cid);
	void StopEnergy(int cid);
	
	void SetupMap(int mapID, int width, int height);
	void SetupPickups();
	
	void UpdateCharacter(int cid, float x, float y, float dir, bool shot, bool energyStart, float health, float bl, float el);

	Map* GetMap();
};

#endif