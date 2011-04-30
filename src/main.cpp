#include <iostream>
#include <ncurses.h>

#include "messagebox.hpp"

#define MESSAGEBOX_HEIGHT 5

// Main window
WINDOW *window;

int main( int argc, char **argv )
{
	initscr();
	noecho();

	int screenX, screenY;
	getmaxyx( stdscr, screenY, screenX );

	window = newwin( screenY-MESSAGEBOX_HEIGHT, screenX, MESSAGEBOX_HEIGHT, 0 );
	box( window, 0, 0 );
	wborder( window, '|', '|', ' ', '-', '|', '|', '+', '+' );

	MessageBox messageBox;
	messageBox.Init( Coord(0,0), Coord( screenX, MESSAGEBOX_HEIGHT ) );
	messageBox.message = "Hello stranger.";
	refresh();
	messageBox.Draw();

	mvwprintw( window, 0, 1, "Content goes here!" );
	wrefresh( window );


	getch();
	endwin();
	return 0;
}

