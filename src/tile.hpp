#ifndef _TILE_HPP_
#define _TILE_HPP_

#include "enums.hpp"
#include "coord.hpp"


struct Tile
{
	Coord location;
	int   sign;
	int   color;
	bool  walkable;
};

#endif

