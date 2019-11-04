//Blake Sullivan - StateHeader.h
#ifndef STATEHEADER_H
#define STATEHEADER_H

#include <string>
using std::string;

namespace GameFlowType
{
	const int AI_SEARCH_H = 10;
	const int AI_SEARCH_A = 11;
	const int AI_SEARCH_E = 12;
	const int AI_SEARCH_O = 0;

	const int AI_HEALTH = 0;
	const int AI_AMMO = 1;
	const int AI_ENERGY = 2;
	const int AI_OPPONENT = 3;
	const int AI_FIGHT = 4;
	const int AI_FLEE = 5;
};

enum States
{
	stateDead = -1,
	stateInactive = 0,
	stateAlive = 1,
	stateRespawn = 2
};
enum ObjectTypes
{
	typeCharacter = 0,
	typePickup = 1,
	typeBullet = 2,
	typeTile = 3,
	typeExplosion = 4
};
enum PickupType
{
	ptHealth = 0,
	ptAmmo = 1,
	ptEnergy = 2
};
enum TileType
{
	ttNormal = 0,
	ttPickupHealth = 20,
	ttPickupAmmo = 21,
	ttPickupSpecial = 22,
	ttSpawnPoint = 23
};
enum BulletType
{
	btBullet = 0,
	btMissile = 1,
	btLaser = 2
};
enum Music
{
	musicMap0 = 0, //0
	musicMap1, //1
	musicMap2, //2
	musicMap3, //3
	musicMenus, //4
	musicResult //5
};
enum Sounds
{
	soundBullet = 0, // 0
	soundMissile, //1
	soundLaser, //2
	soundExplosion, //3
	soundJet, //4
	soundRadar, //5
	soundStealth, //6
	soundPickup, //7
	soundDead, //8
};
#endif