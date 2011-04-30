#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <ncurses.h>

#include "entity.hpp"



class Player : public Entity
{
 public:
	Stats  stats;

	Player();
};

#endif

