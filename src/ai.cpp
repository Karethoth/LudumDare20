#include "ai.hpp"


void MainCharacterAI( NPC *me )
{
	map.Draw( window, Coord( 0, 0 ) );
	if( gameState == mainGame )
	{
		FollowPlayerAI( me );
	}
	else if( me->location.x == me->goal.x &&
			     me->location.y == me->goal.y )
	{
		if( me->waypoint == 0 )
		{
			if( IntroOver() )
				me->waypoint++;
		}
		else if( me->waypoint == 1 )
		{
			if( StartMainGame() )
				me->waypoint++;
		}
		else if( me->waypoint == 2 )
		{
			messageBox.message[0] = "King: That's a good son. You'll make a great king someday.";
			messageBox.message[2] = "->";
			messageBox.Draw();
			refresh();
			wrefresh( messageBox.window );
			getch();
			EndGame();
		}
	}
	else
	{
		Direction d = NextMove( me->location, me->goal );
		me->location = DirectionToCoord( me->location, d );
	}
	map.Draw( window, Coord( 0, 0 ) );
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
	
	player->location = tgt;

	if( next.x == tgt.x && next.y == tgt.y )
	{
		vector<Coord> neighbours = Neighbours( me->location );
		int max = neighbours.size();
		if( max )
		{
			int next = rand() % max;
			me->location = neighbours.at( next );
		}
	}
	else
	{
		me->location = next;
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

