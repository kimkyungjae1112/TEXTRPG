#pragma once
#ifndef __IBATTLESYSTEM_H__
#define __IBATTLESYSTEM_H__

class BattleSystem
{
public:
	virtual void Attack() = 0;
	virtual void Defend() = 0;
	virtual void Run() = 0;
	virtual ~BattleSystem() {}
};

#endif //__IBATTLESYSTEM_H__