#include "ai.hpp"


void MainCharacterAI( NPC *me )
{
	if( me->location.x != me->goal.x ||
			me->location.y != me->goal.y )
	{
		Direction d = NextMove( me->location, me->goal );
		me->location = DirectionToCoord( me->location, d );
	}
	//else
	//{
	//	clear();
	//	map.Clear();
	//	map.Load( "map2.dat", player, mainCharacter );
	//}
}



void StationaryNPCAI( NPC *me )
{
}


void FollowPlayerAI( NPC *me )
{
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



void MonsterAI( NPC *me )
{
	if( !me->alive )
	{
		return;
	}

	if( me->hostile )
	{
		// Check who's closer, main character or player
		int deltaMain = Heuristic( me->location, mainCharacter->location );
		int deltaPlayer = Heuristic( me->location, player->location );

		// Side note: this might lead to some interesting behaviour..
		Coord target = deltaPlayer <= deltaMain ? player->location : mainCharacter->location;
		Entity *targetEntity = deltaPlayer <= deltaMain ? (Entity*)player : mainCharacter;

		// If we can attack the target..
		if( Heuristic( me->location, target ) <= me->stats.attackRange )
		{
				Attack( me, targetEntity );
		}

		// If we can't attack, move closer if we can see the player
		else
		{
			me->goal = target;

			if( Heuristic( me->location, target ) <= me->stats.sight )
			{
				targetEntity->location = Coord( 0,0 );
				Direction d = NextMove( me->location, target );
				me->location = DirectionToCoord( me->location, d );
				targetEntity->location = target;
			}
		}
	}
	else
	{
	}
}

