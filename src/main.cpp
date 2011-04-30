#include <iostream>
#include <ncurses.h>

#include "messagebox.hpp"
#include "map.hpp"
#include "player.hpp"
#include "maincharacter.hpp"
#include "ai.hpp"

using std::string;

#define MESSAGEBOX_HEIGHT 5


// Main window
WINDOW *window;
Player *player;
MainCharacter *mainCharacter;
Coord  screenSize;
Map    map;


bool IsMovable( Coord tgt )
{
	bool isMovable = true;
	vector<Tile*>::iterator t;
	for( t = map.tiles.begin();
			 t != map.tiles.end();
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
	
	vector<NPC*>::iterator e;
	for( e = map.npcs.begin();
			 e != map.npcs.end();
			 e++ )
	{
		if( (*e)->location.x == tgt.x &&
				(*e)->location.y == tgt.y )
		{
			isMovable = false;
			break;
		}
	}
	return isMovable;
}


void Intro()
{
	char buffer[80];
	MessageBox msgBox;
	msgBox.Init( Coord( 0, 0 ), screenSize );
	echo();
	refresh();
	msgBox.message = "\"It's dangerous to go alone. Take this.\"";
	msgBox.Draw();
	wrefresh( msgBox.window );
	getch();
	curs_set( 0 );
	noecho();
}



Direction KeyToDirection( int key )
{
	Direction d = invalid;

	switch( key )
	{
		case 'k':
			d = north;
			break;

		case 'l':
			d = east;
			break;

		case 'j':
			d = south;
			break;

		case 'h':
			d = west;
			break;

		default:
			d = invalid;
	}
	return d;
}



Coord DirectionToCoord( Coord cur, Direction d )
{
	if( d == north )
		cur.y--;

	else if( d == east )
		cur.x++;

	else if( d == south )
		cur.y++;

	else if( d == west )
		cur.x--;

	return cur;
}



void Update( int input )
{
	mainCharacter->AIFunction( mainCharacter );
	Direction d = KeyToDirection( input );
	if( d != invalid )
	{
		Coord newCoord = DirectionToCoord( player->location, d );
		if( IsMovable( newCoord ) )
				player->location = newCoord;
	}
}



int main( int argc, char **argv )
{
	initscr();
	noecho();
	curs_set( 0 );

	start_color();
	init_pair( 1, COLOR_GREEN, COLOR_BLACK );

	player = new Player();
	mainCharacter = new MainCharacter();

	getmaxyx( stdscr, screenSize.y, screenSize.x );
	Intro();

	window = newwin( screenSize.y-MESSAGEBOX_HEIGHT, screenSize.x, MESSAGEBOX_HEIGHT, 0 );
	box( window, 0, 0 );
	wborder( window, '|', '|', ' ', '-', '|', '|', '+', '+' );

	MessageBox messageBox;
	messageBox.Init( Coord(0,0), Coord( screenSize.x, MESSAGEBOX_HEIGHT ) );
	refresh();
	messageBox.Draw();
	wprintw( messageBox.window, "You're now the companion of the main character!\n|Protect him!" );
	wrefresh( messageBox.window );

	if( !map.Load( string("map.dat"), player, mainCharacter ) )
			std::cout << "Couldn't load the map!";

	mainCharacter->AIFunction = MainCharacterAI;
	map.npcs.push_back( (NPC*)mainCharacter );

	while( true )
	{
		wrefresh( messageBox.window );

		map.Draw( window, Coord( 0, 0 ) );

		mvwaddch( window, player->location.y,
											player->location.x+1,
											'c' );

		attron( COLOR_PAIR( 1 ) );
		mvwaddch( window, mainCharacter->location.y,
											mainCharacter->location.x+1,
											'@' );
		attroff( COLOR_PAIR( 1 ) );

		wrefresh( window );
		move( screenSize.y-1, screenSize.x-1 );

		int input = getch();

		if( input == 'q' )
				break;

		Update( input );
	}

	endwin();
	return 0;
}

