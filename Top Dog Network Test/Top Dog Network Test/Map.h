//Blake Sullivan - Map.h
#ifndef MAP_H
#define MAP_H

#include "SDL_gfxPrimitives.h" 
#include "Tile.h"
#include <vector>
//#include <iostream>
//#include <string>
#include <fstream>
using std::vector;
using std::fstream;

class Map
{
private:
	vector<Tile*> m_vTiles;
	vector<Tile*>::iterator m_vTilesIT;
	SDL_Surface* m_pMap;

public:
	Map();
	~Map();

	void SetupMap(int iWidth, int iHeight, string sMapName, vector<Object*>& vObj);

	void DrawMap(SDL_Surface* screen, float winX, float winY);

	void AddTile(int r, int c, int x, int y, int pp, vector<Object*>& vObj);
	Tile* GetTile(int x, int y);
	Tile* GetTileFromRC(int x, int y);

	void SetMap(string);
	SDL_Surface* GetMap();

	Tile* FindEmptyPickupPoint(int iPickupType);
};
#endif