#include "MapSearchNode.h"
#include "PathFinder.h"
// Definitions

// map helper functions

bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{

	// same state in a maze search is simply when (x,y) are the same
	if( (x == rhs.x) &&
		(y == rhs.y) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

/*void MapSearchNode::PrintNodeInfo(SDL_Surface* screen, int width, int height, int tile)
{
	//cout << "Node position : (" << x << ", " << y << ")" << endl;
	filledCircleRGBA(screen, x * width + tile/2, y * height + tile/2,5,0,255,255,255);
}*/

// Here's the heuristic function that estimates the distance from a Node
// to the Goal. 

double MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	double xd = fabs(double(((double)x - (double)nodeGoal.x)));
	double yd = fabs(double(((double)y - (double)nodeGoal.y)));

	return xd + yd;
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	if( (x == nodeGoal.x) &&
		(y == nodeGoal.y) )
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{

	int parent_x = -1; 
	int parent_y = -1; 

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}
	

	MapSearchNode NewNode;

	// push each possible move except allowing the search to go backwards

	if( (GetMap( x-1, y ) < 9) && !((parent_x == x-1) && (parent_y == y)) )
	{
		NewNode = MapSearchNode( x-1, y, m_vpMap );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x , y-1 ) < 9) && !((parent_x == x) && (parent_y == y-1)) )
	{
		NewNode = MapSearchNode( x, y-1, m_vpMap );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x+1, y ) < 9) && !((parent_x == x+1) && (parent_y == y)) ) 
	{
		NewNode = MapSearchNode( x+1, y, m_vpMap );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x, y+1 ) < 9) && !((parent_x == x) && (parent_y == y+1)) )
	{
		NewNode = MapSearchNode( x, y+1, m_vpMap );
		astarsearch->AddSuccessor( NewNode );
	}	

	//Checking for diagonals
	if( (GetMap( x-1, y+1 ) < 9) && !((parent_x == x-1) && (parent_y == y+1)) )
	{
		NewNode = MapSearchNode( x-1, y+1, m_vpMap );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x-1 , y-1 ) < 9) && !((parent_x == x-1) && (parent_y == y-1)) )
	{
		NewNode = MapSearchNode( x-1, y-1, m_vpMap );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x+1, y-1 ) < 9) && !((parent_x == x+1) && (parent_y == y-1)) ) 
	{
		NewNode = MapSearchNode( x+1, y-1, m_vpMap );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x+1, y+1 ) < 9) && !((parent_x == x+1) && (parent_y == y+1)) )
	{
		NewNode = MapSearchNode( x+1, y+1, m_vpMap );
		astarsearch->AddSuccessor( NewNode );
	}	

	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is 
// conceptually where we're moving

double MapSearchNode::GetCost( MapSearchNode &successor )
{
	return (double) GetMap( x, y );

}

int MapSearchNode::GetMap( int x, int y )
{
	if( x < 0 || x >= 64 || y < 0 || y >= 48)
		{return 9;}

	return (*m_vpMap)[(y*48)+x];
}