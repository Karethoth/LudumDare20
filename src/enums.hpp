#ifndef _ENUMS_HPP_
#define _ENUMS_HPP_

enum Direction
{
	invalid=0,
	below,
	north,
	east,
	south,
	west
};


enum NPCType
{
	unknown=0,
	hero,
	monster
};


enum GameState
{
	stopped=0,
	intro,
	mainGame,
	endGame,
	outro
};

#endif

