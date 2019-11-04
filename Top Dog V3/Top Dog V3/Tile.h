//Blake Sullivan - Tile.h
#ifndef TILE_H
#define TILE_H

#include "Object.h"

class Tile : public Object
{
private:
	//static int ms_iSize;
	int m_iRow, m_iCol;
	//int m_iX, m_iY;
	int m_iWalkable;
	int m_iPicPos;
	bool m_bHasPickup;

public:
	Tile();
	~Tile() {};

	void Init(int r, int c, int x, int y, int s, int pp);

	void Draw(SDL_Surface* screen, float fDeltaTime, float winX, float winY);
	void Update(float fDeltaTime);
	void Collide(Object* obj);
	void Dispose();

	void SetRow(int);
	void SetCol(int);
	//void SetX(int);
	//void SetY(int);
	void SetWalkable(int);
	void SetPicPos(int);
	//static void SetSize(int);
	void SetHasPickup(bool);

	int GetRow();
	int GetCol();
	//int GetX();
	//int GetY();
	int GetWalkable();
	int GetPicPos();
	static float GetSize();
	bool GetHasPickup();
};
#endif