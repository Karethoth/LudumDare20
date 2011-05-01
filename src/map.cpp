#include "map.hpp"

Map::~Map()
{
	Clear();
}

void Map::Clear()
{
	vector<Tile*>::iterator t;
	for( t = tiles.begin();
			 t != tiles.end();
			 t++ )
	{
		delete *t;
	}
	tiles.clear();

	vector<NPC*>::iterator n;
	for( n = npcs.begin();
			 n != npcs.end();
			 n++ )
	{
		if( (*n)->type != hero )
			delete *n;
	}
	npcs.clear();
}



bool Map::Load( string file, Player *player, MainCharacter *mainc )
{
	std::ifstream f;
	f.open( file.c_str(), std::ios::in );
	if( !f.is_open() )
			return false;

	string line;
	unsigned int x=0, y=0;
	char c;
	while( f.good() )
	{
		std::getline( f, line );
		for( x=0; x < line.length(); x++ )
		{
			c = line[x];
			Tile *tmp = new Tile();
			tmp->location = Coord( x, y );
			tmp->walkable = false;
			tmp->sign = c;
			if( c == 'c' )
			{
				player->location = Coord( x, y );
				tmp->sign = '.';
			}
			else if( c == '@' )
			{
				mainc->type = hero;
				mainc->location = Coord( x, y );
				tmp->sign = '.';
			}
			else if( c == 'K' )
			{
				NPC *npc = new NPC();
				npc->name = "King";
				npc->location = Coord( x, y );
			  npc->sign = 'K';
				npc->hostile = false;
				npc->alive = true;
				npc->AIFunction = StationaryNPCAI;
				npcs.push_back( npc );
				tmp->sign = '.';
			}
			else if( c == 'm' )
			{
				NPC *npc = new NPC();
				npc->name = "Monk";
				npc->location = Coord( x, y );
			  npc->sign = 'm';
				npc->hostile = false;
				npc->alive = true;
				npc->AIFunction = FollowPlayerAI;
				npcs.push_back( npc );
				tmp->sign = '.';
			}
			else if( c == 'e' )
			{
				tmp->sign = '.';
			}
			else if( c == 'E' )
			{
				monsterSpawns.push_back( Coord( x, y ) );
				tmp->sign = '.';
			}
			else if( c == '1' )
			{
				mainCharacterPath[0] = Coord( x, y );
				tmp->sign = '.';
			}
			else if( c == '2' )
			{
				mainCharacterPath[1] = Coord( x, y );
				tmp->sign = '.';
			}
			else if( c == '3' )
			{
				mainCharacterPath[2] = Coord( x, y );
				tmp->sign = '.';
			}
			else if( c == '=' )
			{
				doors.push_back( Coord( x, y ) );
				tmp->sign = '.';
			}

			if( tmp->sign == '.' )
			{
					tmp->walkable = true;
			}

			tiles.push_back( tmp );
		}
		y++;
	}
	doorsOpen = false;

	return true;
}



void Map::Draw( WINDOW *window, Coord offset )
{
	vector<Tile*>::iterator t;
	for( t = tiles.begin();
			 t != tiles.end();
			 t++ )
	{
			Tile *curTile = *t;
			mvwaddch( window, curTile->location.y+offset.y,
												curTile->location.x+1+offset.x,
												curTile->sign );
	}

	vector<NPC*>::iterator e;
	for( e = npcs.begin();
			 e != npcs.end();
			 e++ )
	{
		mvwaddch( window, (*e)->location.y+offset.y,
						          (*e)->location.x+1+offset.x,
											(*e)->sign );
	}

	if( !doorsOpen )
	{
	  vector<Coord>::iterator d;
		for( d = doors.begin();
				 d != doors.end();
				 d++ )
		{
			mvwaddch( window, (*d).y+offset.y,
												(*d).x+1+offset.x,
												'=' );
		}
	}
}



void Map::GenerateMonster( Coord loc )
{
	if( !IsMovable( loc ) )
		return;
	NPC *npc = new NPC();
	npc->name = "Monster";
	npc->location = loc;
	npc->sign = 'e';
	npc->hostile = true;
	npc->alive = true;
	npc->AIFunction = MonsterAI;
	npcs.push_back( npc );
}



void Map::SpawnMonsters( int count )
{
	for( int i=0; i<count; i++ )
	{
		Coord tmp = monsterSpawns[i];
		if( IsMovable( tmp ) )
		{
			GenerateMonster( tmp );
			monsterCount++;
		}
		Draw( window, Coord(0,0) );
	}
}



bool Map::MonstersDead()
{
	vector<NPC*>::iterator n;
	for( n = npcs.begin();
			 n != npcs.end();
			 n++ )
	{
		if( (*n)->hostile )
		{
			if( (*n)->alive && (*n)->name == "Monster" )
				return false;
		}
	}
	return true;
}



void Map::OpenDoors()
{
	doorsOpen = true;
}



void Map::CloseDoors()
{
	doorsOpen = false;
}

