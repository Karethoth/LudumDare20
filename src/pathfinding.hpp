#ifndef _PATHFINDING_HPP_
#define _PATHFINDING_HPP_

#include <cstdlib>
#include <vector>

#include "enums.hpp"
#include "coord.hpp"

using std::vector;

extern bool IsMovable( Coord );


struct CoordNode
{
	CoordNode *parent;

	Coord data;
	int f, g, h;

	CoordNode( Coord d, int f, int g, int h )
	{
		parent = 0;
		data = d;
		this->f = f;
		this->g = g;
		this->h = h;
	}

	CoordNode( const CoordNode &a )
	{
		data = a.data;
		f = a.f;
		g = a.g;
		h = a.h;
		parent = a.parent;
	}
};


unsigned int Heuristic( Coord a, Coord b );
vector<Coord> Neighbours( Coord a );
Direction NextMove( Coord a, Coord b );




#endif

