#ifndef _AI_HPP_
#define _AI_HPP_

#include <cstdlib>
#include <curses.h>

#include "enums.hpp"
#include "entity.hpp"
#include "npc.hpp"
#include "map.hpp"
#include "pathfinding.hpp"
#include "player.hpp"

extern void Attack( Entity*, Entity* );
extern Coord DirectionToCoord( Coord, Direction );
extern bool IsMovable( Coord );
extern WINDOW *window;
extern Player *player;
extern MainCharacter *mainCharacter;
extern Map map;
extern GameState gameState;

extern int IntroOver();
extern int StartMainGame();

void MainCharacterAI( NPC *me );
void StationaryNPCAI( NPC *me );
void FollowPlayerAI( NPC *me );
void MonsterAI( NPC *me );

#endif

