#ifndef _STATS_HPP_
#define _STATS_HPP_

struct Stats
{
	unsigned int maxhp;
	unsigned int hp;
	unsigned int str;

	unsigned int sight;
	unsigned int attackRange;

	Stats( unsigned int Maxhp=10,
				 unsigned int Hp=10,
				 unsigned int Str=2,
				 unsigned int Sight=5,
				 unsigned int AttackRange=1 )
	{
		maxhp = Maxhp;
		hp = Hp;
		str = Str;
		sight = Sight;
		attackRange = AttackRange;
	}
};

#endif

