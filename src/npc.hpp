#ifndef _NPC_HPP_
#define _NPC_HPP_

#include "entity.hpp"


class NPC : public Entity
{
 public:
	virtual ~NPC();

	bool hostile;
	bool AIEnabled;

	//void (*AIFunction)();

	//NPCType type;
};

#endif

