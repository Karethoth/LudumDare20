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


void FollowPlayerAI( NPC *me )
{
	// Very buggy, usually just blocks player
	Coord tgt = player->location;
	// A hack to make this work.
	player->location = Coord( 0, 0 );
	Direction d = NextMove( me->location, tgt );
	Coord next = DirectionToCoord( me->location, d );
	
	if( next.x != tgt.x || next.y != tgt.y )
	{
		me->location = next;
		player->location = tgt;
	}
	else
	{
		player->location = tgt;
		vector<Coord> neighbours = Neighbours( me->location );
		int max = neighbours.size();
		if( max == 0 )
			max = 1;
		int next = rand() % max;
		me->location = neighbours.at( next );
	}
}

