#pragma once
#ifndef __MONSTERBASE_H__
#define __MONSTERBASE_H__
#include <iostream>

enum class MType
{
	GOBLIN,
	OAK,
	BOSS,
	END
};

class MonsterBase
{
public:
	MonsterBase() {}
	virtual void BaseSetMonster(MType Type) = 0;
	virtual ~MonsterBase() {};
};

#endif //__MONSTERBASE_H__