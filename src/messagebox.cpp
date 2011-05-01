#include "messagebox.hpp"

void MessageBox::Init( Coord Location, Coord Size )
{
	location = Location;
	size = Size;
	window = newwin( size.y, size.x, location.y, location.x );
	box( window, 0, 0 );
	wborder( window, '|', '|', '-', '-', '+', '+', '+', '+' );
}



void MessageBox::Draw()
{
	if( size.x == 0 || size.y == 0 )
	{
			return;
	}
	wclear( window );
	mvwprintw( window, 1, 1, message[0].c_str() );
	mvwprintw( window, 2, 1, message[1].c_str() );
	mvwprintw( window, 3, 1, message[2].c_str() );
	mvwprintw( window, 4, 1, message[3].c_str() );
	wborder( window, '|', '|', '-', '-', '+', '+', '+', '+' );
}



void MessageBox::Clear()
{
	Line( 0, "" );
	Line( 1, "" );
	Line( 2, "" );
	Line( 3, "" );
	wclear( window );
	wborder( window, '|', '|', '-', '-', '+', '+', '+', '+' );
	wrefresh( window );
}



void MessageBox::Line( int line, string msg )
{
	message[line] = msg;
}

