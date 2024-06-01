#pragma once
#ifndef __MONSTERTYPE_H__
#define __MONSTERTYPE_H__

class MonsterType : public MonsterBase
{
public:
	MonsterType() : Name(""), Hp(0), Damage(0), Xp(0) {}
	virtual void BaseSetMonster(MType Type) override = 0;

	std::string GetName() const { return Name; }
	int GetHp() const { return Hp; }
	int GetDamage() const { return Damage; }
	int GetXp() const { return Xp; }

	virtual ~MonsterType() {}
protected:
	std::string Name;
	int Hp;
	int Damage;
	int Xp;
};

class Goblin : public MonsterType
{
	virtual void BaseSetMonster(MType Type) override
	{
		Name = "고블린";
		Hp = 200;
		Damage = 10;
		Xp = 5;
	}
};

class Oak : public MonsterType
{
	virtual void BaseSetMonster(MType Type) override
	{
		Name = "오크";
		Hp = 350;
		Damage = 15;
		Xp = 10;
	}
};

class Boss : public MonsterType
{
	virtual void BaseSetMonster(MType Type) override
	{
		Name = "보스";
		Hp = 500;
		Damage = 30;
		Xp = 20;
	}
};
#endif //__MONSTERTYPE_H__