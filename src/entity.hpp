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
	Entity(){};
	virtual ~Entity(){};

	string name;
	Coord  location;
	Coord  goal;
	Stats  stats;
	bool   alive;

	int    sign;
	int		 color;

	virtual void Move( Direction d );
	virtual void Draw();
	virtual void Die();
};

#endif

