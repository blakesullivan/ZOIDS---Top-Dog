//Blake Sullivan - Level.h
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Character.h"
#include "Bullet.h"
#include "Pickup.h"
#include "Map.h"
using namespace std;

class Level
{
private:
	vector<Object*> m_vpObj;
	vector<Object*>::iterator m_vpObjIT;
	Map* m_pMap;
	float m_fWinPosX, m_fWinPosY;

public:
	Level();
	~Level();

	void Init(int myID);
	void Update(float fDeltaTime);

	void AddCharacter(int cID, float x, float y, string name, int state, bool bot);
	void AddCharacter(int cID, string name, bool bot);
	void Draw(SDL_Surface* screen, float fDT);
	Character* GetCharacter(int id);
	
	void AddBullet(int cID, bool bUseAlt = false);

	void AddPickup(int pt, float x, float y);
	void AddPickup(int pt);

	void CheckForCollisions();
	bool CheckCollision(Object* Obj1, Object* Obj2);
	
	Object* GetObject(int id);
	Object* FindNearestObject(int myX, int myY, int searchType, int id, int searchRadius);
	Object* FindFurtherestObject(int myX, int myY, int id);

	void UpdateWindowPos(float, float);

	void StartEnergy(int cid);
	void StopEnergy(int cid);

	void SetupMap(int mapID, int width, int height);
	void SetupPickups();

	void UpdateCharacterPos(int cid, float x, float y, float dir);
};

#endif