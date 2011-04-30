#ifndef _NPC_HPP_
#define _NPC_HPP_

#include "entity.hpp"


class NPC : public Entity
{
 public:
	virtual ~NPC(){};

	bool hostile;
	bool AIEnabled;

	bool (*IsMovable)( Coord );
	void (*AIFunction)( NPC* );

	//NPCType type;
};

#endif

