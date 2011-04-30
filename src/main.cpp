#include <iostream>
#include <ncurses.h>

#include "messagebox.hpp"
#include "map.hpp"
#include "player.hpp"
#include "maincharacter.hpp"

using std::string;

#define MESSAGEBOX_HEIGHT 5


// Main window
WINDOW *window;
Player *player;
MainCharacter *mainCharacter;
Coord  screenSize;
Map    map;


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



void Update( int input )
{
	Direction d = KeyToDirection( input );
}



int main( int argc, char **argv )
{
	initscr();
	noecho();
	curs_set( 0 );

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

	while( true )
	{
		map.Draw( window, Coord( 0, 0 ) );

		mvwaddch( window, player->location.y,
											player->location.x+1,
											'c' );

		mvwaddch( window, mainCharacter->location.y,
											mainCharacter->location.x+1,
											'@' );

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

