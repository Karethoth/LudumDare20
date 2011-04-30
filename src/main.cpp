#include <iostream>
#include <ncurses.h>

#include "messagebox.hpp"
#include "map.hpp"
#include "player.hpp"

using std::string;

#define MESSAGEBOX_HEIGHT 5


// Main window
WINDOW *window;
Player *player;
Coord  screenSize;
Map    map;


void Intro()
{
	char buffer[80];
	MessageBox msgBox;
	msgBox.Init( Coord( 0, 0 ), screenSize );
	echo();
	refresh();
	msgBox.message = "Hello stranger, what might be your name? ";
	msgBox.Draw();
	wrefresh( msgBox.window );
	wgetstr( msgBox.window, buffer );
	player->name = string( buffer );
	curs_set( 0 );
	noecho();
}



int main( int argc, char **argv )
{
	initscr();
	noecho();
	curs_set( 0 );

	player = new Player();

	getmaxyx( stdscr, screenSize.y, screenSize.x );
	Intro();

	window = newwin( screenSize.y-MESSAGEBOX_HEIGHT, screenSize.x, MESSAGEBOX_HEIGHT, 0 );
	box( window, 0, 0 );
	wborder( window, '|', '|', ' ', '-', '|', '|', '+', '+' );

	MessageBox messageBox;
	messageBox.Init( Coord(0,0), Coord( screenSize.x, MESSAGEBOX_HEIGHT ) );
	refresh();
	messageBox.Draw();
	wprintw( messageBox.window, "Hello %s!", player->name.c_str() );
	wrefresh( messageBox.window );

	if( !map.Load( "map.dat" ) )
			std::cout << "Couldn't load the map!";

	map.Draw( window, Coord( 0, 0 ) );

	wrefresh( window );
	move( screenSize.y-1, screenSize.x-1 );


	getch();
	endwin();
	return 0;
}

