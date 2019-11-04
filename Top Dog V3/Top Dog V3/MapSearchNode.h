#ifndef MAPSEARCHNODE_H
#define MAPSEARCHNODE_H

//#include "SDL.h"   /* All SDL App's need this */
#include <stdio.h>
//#include "SDL_gfxPrimitives.h" 

#include <stdlib.h>
#include <time.h>
#include "astar/stlastar.h"
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

//extern int map[  ];
//extern const int MAP_WIDTH;
//extern const int MAP_HEIGHT;
//extern const int TILE_WIDTH;
//extern SDL_Surface *screen;

class MapSearchNode
{
	friend class PathFinder;
public:
	unsigned long x;	 // the (x,y) positions of the node
	unsigned long y;	
	vector<int>* m_vpMap;
	
	MapSearchNode() { x = y = 0; }
	MapSearchNode( unsigned int px, unsigned int py, vector<int>* map) { x=px; y=py; m_vpMap = map;}

	double GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
	bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
	double GetCost( MapSearchNode &successor );
	bool IsSameState( MapSearchNode &rhs );

	//void PrintNodeInfo(SDL_Surface* screen, int width, int height, int tile); 

	int GetMap( int x, int y );
};

#endif