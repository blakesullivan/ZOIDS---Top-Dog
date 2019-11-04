//Blake Sullivan - PathFinder.h
#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "MapSearchNode.h"

class PathFinder
{
private:
	//SDL_Surface* m_pSurface;
	vector<int> m_vMap;
	static int MAP_WIDTH;
	static int MAP_HEIGHT;
	static int TILE_WIDTH;

public:
	PathFinder();

	void Init(int Width, int Height, int TW);
	int findPath( int Ax, int Ay, int Bx, int By, int &Cx, int &Cy, bool display );
	int GetMap( int x, int y );
	int SetMap( int x, int y, int z );
	int SetMap(std::string input);
};

#endif