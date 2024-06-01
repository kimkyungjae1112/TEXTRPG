#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "MonsterBase.h"
#include "MonsterType.h"
#include <memory>

class Monster : public MonsterBase
{
public:
	Monster();
	virtual void BaseSetMonster(MType Type) override;
	
	virtual ~Monster();

	void SetHp(const int& InDamage) { Hp -= InDamage; }
	
	//Get
	std::string GetName() const { return Name; }
	int GetHp() const { return Hp; }
	int GetDamage() const { return Damage; }
	int GetXp() const { return Xp; }

private:
	std::string Name;
	int Hp;
	int Damage;
	int Xp;

	std::unique_ptr<MonsterType> MonsterTyp;
};

#endif //__MONSTER_H__