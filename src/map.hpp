#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <iostream>
#include <vector>
#include <fstream>
#include <curses.h>

#include "enums.hpp"
#include "coord.hpp"
#include "tile.hpp"
#include "entity.hpp"

using std::string;
using std::vector;


class Map
{
 public:
	vector<Tile*>   tiles;
	vector<Entity*> entities;

	bool Load( string file );
	bool IsMovable( unsigned int x, unsigned int y );

	void Draw( WINDOW *window, Coord offset );

	~Map();
};

#endif

