#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <iostream>
#include <vector>
#include <fstream>
#include <curses.h>

#include "enums.hpp"
#include "coord.hpp"
#include "tile.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "npc.hpp"
#include "maincharacter.hpp"

class Map;
#include "ai.hpp"

using std::string;
using std::vector;

extern bool IsMovable( Coord );


class Map
{
 public:
	vector<Tile*> tiles;
	vector<NPC*>  npcs;
	Coord					mainCharacterPath[3];
	vector<Coord> monsterSpawns;
	vector<Coord> doors;
	bool					doorsOpen;

	bool Load( string file, Player *player, MainCharacter *mainc );
	void Clear();

	void Draw( WINDOW *window, Coord offset );
	void GenerateMonster( Coord );
	void SpawnMonsters( int count );

	void OpenDoors();
	void CloseDoors();

	~Map();
};

#endif

