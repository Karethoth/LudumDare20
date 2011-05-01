#include <iostream>
#include <ncurses.h>
#include <ctime>

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
MessageBox messageBox;
bool gameOver = false;



void Attack( Entity *attacker, Entity *defender )
{
	messageBox.message = attacker->name+" attacks "+defender->name+"!";
	messageBox.Draw();
	if( defender->stats.hp >= attacker->stats.str )
			defender->stats.hp -= attacker->stats.str;
	else
			defender->stats.hp = 0;

	if( defender->stats.hp == 0 )
	{
		messageBox.message = defender->name+" dies!";
		messageBox.Draw();
		defender->alive = false;
	}
}



bool IsMovable( Coord tgt )
{
	vector<Tile*>::iterator t;
	for( t = map.tiles.begin();
			 t != map.tiles.end();
			 t++ )
	{
		if( (*t)->location.x == tgt.x &&
				(*t)->location.y == tgt.y )
			if( !(*t)->walkable )
			{
				return false;
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
			return false;
			break;
		}
	}

	if( player->location.x == tgt.x &&
			player->location.y == tgt.y )
		return false;
	return true;
}



void Intro()
{
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



void PlayerDied()
{
	messageBox.message = "You died. You have given your life to the mission, but you won't see how it ends.";
	messageBox.Draw();
	gameOver = true;
}



void MainCharacterDied()
{
	messageBox.message = "The hero has died. You failed at your mission.";
	messageBox.Draw();
	gameOver = true;
}



void EndGame()
{
	messageBox.Draw();
	wrefresh( messageBox.window );
	getch();
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
	Direction d = KeyToDirection( input );
	if( d != invalid )
	{
		Coord newCoord = DirectionToCoord( player->location, d );
		if( IsMovable( newCoord ) )
				player->location = newCoord;
	}

	if( mainCharacter )
		mainCharacter->AIFunction( mainCharacter );

	vector<NPC*>::iterator e;
	for( e = map.npcs.begin();
			 e < map.npcs.end();
			 e++ )
	{
		if( !(*e) )
		{
			map.npcs.erase( e );
			continue;
		}

		if( (*e)->alive == false )
		{
			(*e)->Die();
			map.npcs.erase( e );
			continue;
		}

		if( (*e)->AIFunction )
		{
			(*e)->AIFunction( (*e) );
		}
	}

	if( !player->alive )
	{
		PlayerDied();
	}

	if( mainCharacter )
		if( !mainCharacter->alive )
		{
			MainCharacterDied();
			delete mainCharacter;
			mainCharacter = 0;
		}

	if( gameOver )
	{
		EndGame();
	}
}



int main( int argc, char **argv )
{
	// New seed
	srand( time( NULL ) );
	initscr();
	noecho();
	curs_set( 0 );

	start_color();
	init_pair( 1, COLOR_GREEN, COLOR_BLACK );

	player = new Player();
	player->name ="Player";
	player->alive = true;

	mainCharacter = new MainCharacter();

	getmaxyx( stdscr, screenSize.y, screenSize.x );
	Intro();

	window = newwin( screenSize.y-MESSAGEBOX_HEIGHT, screenSize.x, MESSAGEBOX_HEIGHT, 0 );
	box( window, 0, 0 );
	wborder( window, '|', '|', ' ', '-', '|', '|', '+', '+' );

	messageBox.Init( Coord(0,0), Coord( screenSize.x, MESSAGEBOX_HEIGHT ) );
	refresh();
	messageBox.Draw();
	wprintw( messageBox.window, "You're now the companion of the main character!\n|Protect him! Use h,j,k,l keys to move!" );
	wrefresh( messageBox.window );

	if( !map.Load( string("map.dat"), player, mainCharacter ) )
			std::cout << "Couldn't load the map!";

	mainCharacter->name = "Hero";
	mainCharacter->AIFunction = MainCharacterAI;
	mainCharacter->sign = '@';
	map.npcs.push_back( (NPC*)mainCharacter );

	while( true )
	{
		wrefresh( messageBox.window );

		map.Draw( window, Coord( 0, 0 ) );

		mvwaddch( window, player->location.y,
											player->location.x+1,
											'c' );

		wrefresh( window );
		move( screenSize.y-1, screenSize.x-1 );

		int input = getch();

		if( input == 'q' )
				break;

		Update( input );

		if( gameOver )
			break;
	}

	endwin();
	return 0;
}

