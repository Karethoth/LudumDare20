#ifndef _MESSAGEBOX_HPP_
#define _MESSAGEBOX_HPP_

#include <iostream>
#include <ncurses.h>

#include "coord.hpp"

using std::string;


class MessageBox
{
 public:
	WINDOW *window;
	Coord location;
	Coord size;

	void Init( Coord, Coord );

	string message[4];
	void Draw();
	void Clear();
	void Line( int, string );
};

#endif

