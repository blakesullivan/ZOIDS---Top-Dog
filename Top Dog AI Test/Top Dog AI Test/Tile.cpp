//Blake Sullivan - Tile.cpp
#include "Tile.h"

//int Tile::ms_iSize = 32;

Tile::Tile()
{
	SetRow(-1);
	SetCol(-1);
	SetX(-1);
	SetY(-1);
	SetWalkable(0);
	SetSize(0);
	SetHasPickup(false);
}

void Tile::Init(int r, int c, int x, int y, int s, int pp)
{
	SetRow(r);
	SetCol(c);
	SetX(x);
	SetY(y);
	SetType(typeTile);
	SetID(pp);
	if (pp == 0 || pp >= ttPickupHealth)
	{
		SetWalkable(0);
		SetState(stateDead);
		SetDamage(0);
	}
	else
	{
		SetWalkable(9);
		SetState(stateAlive);
		SetDamage(1);
	}
	SetSize(s);
	SetPicPos(pp);
	SetHasPickup(false);
}

void Tile::Draw(SDL_Surface* screen, float fDeltaTime, float winX, float winY)
{
}
void Tile::Update(float fDeltaTime)
{
}
void Tile::Collide(Object* obj)
{
}
void Tile::Dispose()
{
}


void Tile::SetRow(int r)
{
	m_iRow = r;
}
void Tile::SetCol(int c)
{
	m_iCol = c;
}
/*void Tile::SetX(int x)
{
	m_iX = x;
}
void Tile::SetY(int y)
{
	m_iY = y;
}*/
void Tile::SetWalkable(int w)
{
	m_iWalkable = w;
}
void Tile::SetPicPos(int pp)
{
	m_iPicPos = pp;
}
/*void Tile::SetSize(int s)
{
	ms_iSize = s;
}*/

int Tile::GetRow()
{
	return m_iRow;
}
int Tile::GetCol()
{
	return m_iCol;
}
/*int Tile::GetX()
{
	return m_iX;
}
int Tile::GetY()
{
	return m_iY;
}*/
int Tile::GetWalkable()
{
	return m_iWalkable;
}
int Tile::GetPicPos()
{
	return m_iPicPos;
}
float Tile::GetSize()
{
	return 32;
}

void Tile::SetHasPickup(bool hp)
{
	m_bHasPickup = hp;
}
bool Tile::GetHasPickup()
{
	return m_bHasPickup;
}