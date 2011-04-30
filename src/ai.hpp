#ifndef _AI_HPP_
#define _AI_HPP_

#include "entity.hpp"
#include "npc.hpp"
#include "map.hpp"

extern Coord DirectionToCoord( Coord, Direction );
extern bool IsMovable( Coord );

void MainCharacterAI( NPC *me );

#endif

