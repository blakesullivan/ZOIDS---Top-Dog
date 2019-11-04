//Blake Sullivan - PathFinder.cpp
#include "PathFinder.h"
#include "MapSearchNode.h"

int PathFinder::MAP_WIDTH = 0;
int PathFinder::MAP_HEIGHT = 0;
int PathFinder::TILE_WIDTH = 0;

PathFinder::PathFinder()
{
	//m_pSurface = NULL;
	MAP_WIDTH = 0;
	MAP_HEIGHT = 0;
	TILE_WIDTH = 0;
}

void PathFinder::Init(int Width, int Height, int TW)
{
	MAP_WIDTH = Width;
	MAP_HEIGHT = Height;
	TILE_WIDTH = TW;
	//m_pSurface = screen;
	
	for (int i = 0; i < (MAP_WIDTH*MAP_HEIGHT); i++)
	{
		m_vMap.push_back(-1);
	}
}

int PathFinder::GetMap( int x, int y )
{
	if( x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
		{return 9;}

	return m_vMap[(y*MAP_WIDTH)+x];
}
int PathFinder::SetMap( int x, int y, int z )
{

	if( x < 0 || x >= (MAP_WIDTH) || y < 0 || y >= (MAP_HEIGHT))
		{return 0;}

	m_vMap[(y*(MAP_WIDTH))+x]=z;
	return 1;
}
int PathFinder::SetMap(std::string input)
{
	int iTemp = 0;
	std::string sTemp = input;
	for (int i = 0; i < (MAP_WIDTH * MAP_HEIGHT); i++)
	{
		iTemp = atoi(sTemp.substr(0, sTemp.find(",")).c_str());
		sTemp = sTemp.substr(sTemp.find(",") + 1, sTemp.length());
		m_vMap[i] = iTemp;
	}
	return 1;
}

//							FROM		TO				NEXT SPOT
int PathFinder::findPath( int Ax, int Ay, int Bx, int By, int &Cx, int &Cy, bool display )
{
	long result=1;
	//cout << "STL A* Search implementation\n(C)2001 Justin Heyes-Jones\n";

	// Our sample problem defines the world as a 2d array representing a terrain
	// Each element contains an integer from 0 to 5 which indicates the cost 
	// of travel across the terrain. Zero means the least possible difficulty 
	// in travelling (think ice rink if you can skate) whilst 5 represents the 
	// most difficult. 9 indicates that we cannot pass.

	// Create an instance of the search class...
	AStarSearch<MapSearchNode> astarsearch;

	unsigned long SearchCount = 0;

	const unsigned long NumSearches = 1;

	while(SearchCount < NumSearches)
	{

		// Create a start state
		MapSearchNode nodeStart;
		nodeStart.x = Ax;
		nodeStart.y = Ay;
		nodeStart.m_vpMap = &m_vMap;

		// Define the goal state
		MapSearchNode nodeEnd;
		nodeEnd.x = Bx;
		nodeEnd.y = By;
		nodeEnd.m_vpMap = &m_vMap;
		
		// Set Start and goal states
		
		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned long SearchState;
		unsigned long SearchSteps = 0;

		do
		{
			SearchState = astarsearch.SearchStep();

			SearchSteps++;

	

		}
		while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

		if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
		{
			//cout << "Search found goal state\n";

				MapSearchNode *node = astarsearch.GetSolutionStart();

				long steps = 0;

				//if (display) node->PrintNodeInfo(m_pSurface, MAP_WIDTH, MAP_HEIGHT, TILE_WIDTH);
				for( ;; )
				{
					node = astarsearch.GetSolutionNext();

					if( !node )
					{
						break;
					}
					if (steps==0)
					{
						Cx = node->x;
						Cy = node->y;
					}
					//if (display) node->PrintNodeInfo(m_pSurface, MAP_WIDTH, MAP_HEIGHT, TILE_WIDTH);
					steps ++;
				
				};

				//cout << "Solution steps " << steps << endl;

				// Once you're done with the solution you can free the nodes up
				astarsearch.FreeSolutionNodes();

	
		}
		else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED ) 
		{
			cout << "Search terminated. Did not find goal state\n";
			result=0;
		
		}

		// Display the number of loops the search went through
		//cout << "SearchSteps : " << SearchSteps << "\n";

		SearchCount ++;

		astarsearch.EnsureMemoryFreed();
	}
	return result;
}

