//Blake Sullivan - StateHeader.h
#ifndef STATEHEADER_H
#define STATEHEADER_H

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
	typeTile = 3
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
	ttPickup = 20
};
enum BulletType
{
	btBullet = 0,
	btMissile = 1,
	btLaser = 2
};
#endif