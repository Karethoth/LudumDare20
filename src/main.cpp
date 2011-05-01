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
GameState gameState = intro;
int round = 0;
bool spawned = false;
int monsterCount=0;


int IntroOver()
{
	messageBox.message[0] = "Prince: \"Hey, you. Come with me.\"";
	messageBox.Draw();
	refresh();
	wrefresh( messageBox.window );

	map.OpenDoors();

	// continue
	mainCharacter->goal = map.mainCharacterPath[1];
	return 1;
}



int StartMainGame()
{
	if( player->location.y > mainCharacter->location.y )
	{
		map.CloseDoors();

		messageBox.Clear();
		messageBox.message[0] = "Prince: \"I-I'll j-just follow you.. Please?\"";
		messageBox.Draw();
		refresh();
		wrefresh( messageBox.window );

		// continue
		gameState = mainGame;
		round = 1;
		return 1;
	}
	else
	{
		messageBox.message[0] = "Prince: \"C-come on.. You may go in first.\"";
		messageBox.Draw();
		refresh();
		wrefresh( messageBox.window );
	}
	return 0;
}



void Attack( Entity *attacker, Entity *defender )
{
	messageBox.message[0] = attacker->name+" attacks "+defender->name+"!";
	messageBox.Draw();
	if( defender->stats.hp >= attacker->stats.str )
			defender->stats.hp -= attacker->stats.str;
	else
			defender->stats.hp = 0;

	if( defender->stats.hp == 0 )
	{
		messageBox.message[0] = defender->name+" dies!";
		messageBox.Draw();
		defender->alive = false;
		if( defender->hostile )
			monsterCount--;
		defender->hostile = false;
	}
}



void PlayerAttack( Coord tgt )
{
	NPC *target = 0;
	vector<NPC*>::iterator e;
	for( e = map.npcs.begin();
			 e != map.npcs.end();
			 e++ )
	{
		if( (*e)->location.x == tgt.x &&
				(*e)->location.y == tgt.y )
		{
			target = *e;
			break;
		}
	}
	
	if( target )
		if( target->hostile )
		{
			Attack( player, target );
		}
		else
		{
			// You don't want to do that..
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

	if( !map.doorsOpen )
	{
		vector<Coord>::iterator d;
		for( d = map.doors.begin();
				 d != map.doors.end();
				 d++ )
		{
			if( (*d).x == tgt.x &&
					(*d).y == tgt.y )
			{
				return false;
				break;
			}
		}
	}
	return true;
}



void Intro()
{
	MessageBox msgBox;
	msgBox.Init( Coord( 0, 0 ), screenSize );
	msgBox.message[0] = "\"Son, it's time for you to show me what you're made of. Slay";
	msgBox.message[1] = " some monsters in the dungeon. Yes, it's dangerous to go alone,";
	msgBox.message[2] = " so take the player with you. He is in the next room waiting.\"",
	msgBox.Draw();
	refresh();
	wrefresh( msgBox.window );
	getch();
}



void PlayerDied()
{
	messageBox.message[0] = "You died. You have given your life to the mission, but you won't see how it ends.";
	messageBox.Draw();
	gameOver = true;
}



void MainCharacterDied()
{
	messageBox.message[0] = "The hero has died. You failed at your mission.";
	messageBox.Draw();
	gameOver = true;
}



void EndGame()
{
	// Messages..
	messageBox.message[0] = "Game is over. Yes, it's over already.";
	messageBox.message[1] = "Thanks for playing, have a nice day!";
	messageBox.Draw();
	wrefresh( messageBox.window );
	gameOver = true;
}



void Outro()
{
	map.OpenDoors();
	messageBox.message[0] = "Prince: \"Finally it's over! I'm out of here.\"";
	messageBox.Draw();
	mainCharacter->AIFunction = MainCharacterAI;
	mainCharacter->goal = map.mainCharacterPath[2];
	gameState = endGame;
}



Direction KeyToDirection( int key )
{
	Direction d = invalid;

	switch( key )
	{
		case 'k':
		case KEY_UP:
			d = north;
			break;

		case 'l':
		case KEY_RIGHT:
			d = east;
			break;

		case 'j':
		case KEY_DOWN:
			d = south;
			break;

		case 'h':
		case KEY_LEFT:
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
		else
			PlayerAttack( newCoord );
	}

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
			delete (*e);
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

	if( round && !spawned )
	{
		map.SpawnMonsters( 1 );
		spawned = true;
	}
	else if( spawned )
	{
		if( map.MonstersDead() || monsterCount < 1 )
		{
			messageBox.message[0] = "More monsters..";
			messageBox.Draw();
			switch( round )
			{
				case 1:
					round++;
					map.SpawnMonsters( 3 );
					break;
				case 2:
					round++;
					map.SpawnMonsters( 6 );
					break;
				case 3:
					round++;
					map.SpawnMonsters( 8 );
					break;
				case 4:
					messageBox.message[0] = "Monsters are dead.. For good this time.";
					messageBox.Draw();
					Outro();
					break;
			}
		}
	}
}



int main( int argc, char **argv )
{
	// New seed
	srand( time( NULL ) );
	initscr();
	noecho();
	curs_set( 0 );
	keypad( stdscr, true );

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


	if( !map.Load( string("map.dat"), player, mainCharacter ) )
	{
		std::cout << "Couldn't load the map!";
		endwin();
		return 1;
	}

	mainCharacter->name = "Prince";
	mainCharacter->hostile = false;
	mainCharacter->alive = true;
	mainCharacter->goal = map.mainCharacterPath[0];
	mainCharacter->AIFunction = MainCharacterAI;
	mainCharacter->sign = '@';
	map.npcs.push_back( (NPC*)mainCharacter );

	map.Draw( window, Coord( 0, 0 ) );
	wrefresh( window );

	messageBox.Init( Coord(0,0), Coord( screenSize.x, MESSAGEBOX_HEIGHT ) );
	messageBox.message[0] = "Prince: Do I really have to?";
	messageBox.message[2] = "->";
	messageBox.Draw();
	refresh();
	wrefresh( messageBox.window );

	getch();
	messageBox.message[0] = "King: If you want to sit on this throne in the future, yes.";
	messageBox.message[2] = "->";
	messageBox.Draw();
	refresh();
	wrefresh( messageBox.window );

	getch();
	messageBox.message[0] = "Prince: Ugh... Well I'll go then.";
	messageBox.message[2] = "->";
	messageBox.Draw();
	refresh();
	wrefresh( messageBox.window );

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

		messageBox.Clear();
		Update( input );

		if( gameOver )
			break;
	}

	getch();

	endwin();
	return 0;
}

