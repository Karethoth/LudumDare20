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

	mvwprintw( window, 1, 1, message.c_str() );
}

