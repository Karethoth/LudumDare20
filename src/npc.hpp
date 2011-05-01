#ifndef _NPC_HPP_
#define _NPC_HPP_

#include "entity.hpp"


class NPC : public Entity
{
 public:
	NPC();
	virtual ~NPC(){};

	bool hostile;
	NPCType type;

	void (*AIFunction)( NPC* );

	void Die();
};

#endif

