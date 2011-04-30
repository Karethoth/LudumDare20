#include "ai.hpp"


void MainCharacterAI( NPC *me )
{
	Coord tgt;

	tgt = DirectionToCoord( me->location, south );
	if( IsMovable( tgt ) )
		me->location = tgt;
	else
	{
		tgt = DirectionToCoord( me->location, north );
		if( IsMovable( tgt ) )
			me->location = DirectionToCoord( me->location, north );
	}
}



void StationaryNPCAI( NPC *me )
{
}
