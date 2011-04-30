#ifndef _MESSAGEBOX_HPP_
#define _MESSAGEBOX_HPP_

#include <iostream>
#include <ncurses.h>

#include "coord.hpp"

using std::string;


class MessageBox
{
 private:
	WINDOW *window;

 public: // No time to play with getters and setters.
	Coord location;
	Coord size;

	string message;
	void Draw();

	void Init( Coord Location, Coord Size );
};

#endif

