#include "pathfinding.hpp"

int _abs( int a )
{
	if( a < 0 )
		return 0-a;
	return a;
}

int Heuristic( Coord a, Coord b )
{
	int A = _abs( b.x - a.x );
	int B = _abs( b.y - b.y );
	return A+B;
}

vector<Coord> Neighbours( Coord a )
{
	vector<Coord> neighbours;

	if( IsMovable( Coord( a.x, a.y+1 ) ) )
		neighbours.push_back( Coord( a.x, a.y+1 ) );

	if( IsMovable( Coord( a.x, a.y-1 ) ) )
		neighbours.push_back( Coord( a.x, a.y-1 ) );

	if( IsMovable( Coord( a.x+1, a.y ) ) )
		neighbours.push_back( Coord( a.x+1, a.y ) );

	if( IsMovable( Coord( a.x-1, a.y ) ) )
		neighbours.push_back( Coord( a.x-1, a.y ) );

	return neighbours;
}



Direction NextMove( Coord a, Coord b )
{
	int maxTries = 1000;
	int tries = 0;
	vector<CoordNode*> openList;
	vector<CoordNode*> closedList;
	CoordNode *tmp = new CoordNode( a, 0, 0, 0 );
	openList.push_back( tmp );
	while( openList.size() > 0 )
	{
		if( tries++ > maxTries )
			break;

		unsigned int lowInd = 0;
		for( unsigned int i=0; i < openList.size(); i++ )
		{
			if( openList.at( i )->f < openList[lowInd]->f )
					lowInd = i;
		}
		CoordNode *currentNode = openList.at( lowInd );

		if( currentNode->data.x == b.x &&
				currentNode->data.y == b.y )
		{
			CoordNode *firstNode = currentNode;
			while( firstNode->parent )
			{
					if( firstNode->parent->parent )
							firstNode = firstNode->parent;
					else break;
			}

			if( firstNode->data.x > a.x )
					return east;

			else if( firstNode->data.x < a.x )
					return west;

			else if( firstNode->data.y > a.y )
					return south;

			else if( firstNode->data.y < a.y )
					return north;
			else return invalid;
		}

		openList.erase( openList.begin()+lowInd );
		closedList.push_back( currentNode );

		vector<Coord> neighbours = Neighbours( currentNode->data );

		vector<Coord>::iterator n;
		for( n = neighbours.begin();
				 n != neighbours.end();
				 n++ )
		{
			CoordNode *neighbour = new CoordNode( (*n),0,0,0 );
			int gScore = currentNode->g + 1;
			bool gScoreIsBest = false;

			CoordNode *existing = 0;
			vector<CoordNode*>::iterator ol;
			for( ol = openList.begin();
					 ol != openList.end();
					 ol++ )
			{
				if( (*ol)->data.x == neighbour->data.x &&
						(*ol)->data.y == neighbour->data.y )
				{
					existing = (*ol);
					break;
				}
			}

			if( !existing )
			{
				existing = neighbour;
				gScoreIsBest = true;
				neighbour->h = Heuristic( neighbour->data, b );
				openList.push_back( neighbour );
			}
			else if( gScore < neighbour->g )
			{
				gScoreIsBest = true;
			}

			if( gScoreIsBest )
			{
				existing->parent = currentNode;
				existing->g = gScore;
				existing->f = neighbour->g + neighbour->h;
			}
		}
	}
	return invalid;
}

