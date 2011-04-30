#include "map.hpp"

Map::~Map()
{
	vector<Tile*>::iterator t;
	for( t = tiles.begin();
			 t != tiles.end();
			 t++ )
	{
		delete *t;
	}

	vector<Entity*>::iterator e;
	for( e = entities.begin();
			 e != entities.end();
			 e++ )
	{
		delete *e;
	}
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
					mainc->location = Coord( x, y );
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
}



bool Map::IsMovable( Coord tgt )
{
	bool isMovable = true;
	vector<Tile*>::iterator t;
	for( t = tiles.begin();
			 t != tiles.end();
			 t++ )
	{
		if( (*t)->location.x == tgt.x &&
				(*t)->location.y == tgt.y )
			if( !(*t)->walkable )
			{
				isMovable = false;
				break;
			}
	}
	return isMovable;
}

