#include <iostream>
#include <ncurses.h>

#include "messagebox.hpp"
#include "player.hpp"

using std::string;

#define MESSAGEBOX_HEIGHT 5


// Main window
WINDOW *window;
Player *player;
Coord  screenSize;


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
}



int main( int argc, char **argv )
{
	initscr();
	noecho();

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

	mvwprintw( window, 0, 1, "Content goes here!" );
	wrefresh( window );


	getch();
	endwin();
	return 0;
}

