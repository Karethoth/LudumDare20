#ifndef _MAINCHARACTER_HPP_
#define _MAINCHARACTER_HPP_

#include "npc.hpp"

class MainCharacter : public NPC
{
 public:
	MainCharacter();
	~MainCharacter();
	int waypoint;
};

#endif

