#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <iostream>

#include "enums.hpp"
#include "coord.hpp"
#include "stats.hpp"

using std::string;


class Entity
{
 public:
	virtual ~Entity(){};

	string name;
	Coord  location;
	Stats  stats;

	int    sign;
	int		 color;

	virtual void Move( Direction d );
	virtual void Draw();
};

#endif

