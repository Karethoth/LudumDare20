#include "ai.hpp"


void MainCharacterAI( NPC *me )
{
	Coord tgt;

	tgt = DirectionToCoord( me->location, south );
	if( IsMovable( tgt ) )
		me->location = tgt;
	else
	{
		me->location = DirectionToCoord( me->location, north );
	}
}

