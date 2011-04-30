#include <iostream>
#include <ncurses.h>

WINDOW *window;

int main( int argc, char **argv )
{
	window = initscr();
	printw( "It works!" );
	refresh();
	getch();
	endwin();
	return 0;
}

