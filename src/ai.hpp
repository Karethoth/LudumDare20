#ifndef _AI_HPP_
#define _AI_HPP_

#include <cstdlib>

#include "entity.hpp"
#include "npc.hpp"
#include "map.hpp"
#include "pathfinding.hpp"
#include "player.hpp"

extern Coord DirectionToCoord( Coord, Direction );
extern bool IsMovable( Coord );
extern Player *player;

void MainCharacterAI( NPC *me );
void StationaryNPCAI( NPC *me );
void FollowPlayerAI( NPC *me );

#endif

