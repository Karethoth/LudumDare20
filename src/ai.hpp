#ifndef _AI_HPP_
#define _AI_HPP_

#include <cstdlib>
#include <curses.h>

#include "entity.hpp"
#include "npc.hpp"
#include "map.hpp"
#include "pathfinding.hpp"
#include "player.hpp"

extern void Attack( Entity*, Entity* );
extern Coord DirectionToCoord( Coord, Direction );
extern bool IsMovable( Coord );
extern Player *player;
extern MainCharacter *mainCharacter;
extern Map map;

void MainCharacterAI( NPC *me );
void StationaryNPCAI( NPC *me );
void FollowPlayerAI( NPC *me );
void MonsterAI( NPC *me );

#endif

