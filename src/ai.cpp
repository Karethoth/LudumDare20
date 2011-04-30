#include "ai.hpp"


void MainCharacterAI( NPC *me )
{
	Coord tgt;

	if( me->location.x != 1 ||
			me->location.y != 1 )
	{
		Direction d = NextMove( me->location, Coord( 1, 1 ) );
		me->location = DirectionToCoord( me->location, d );
	}
}



void StationaryNPCAI( NPC *me )
{
}

