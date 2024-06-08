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

	virtual void InsertDatabase() {}
	virtual ~MonsterType() {}
protected:
	std::string Name;
	int Hp;
	int Damage;
	int Xp;
};

class Goblin : public MonsterType
{
	void InsertDatabase() 
	{
		Name = "Goblin";
		Hp = 200;
		Damage = 10;
		Xp = 5;
	}
	virtual void BaseSetMonster(MType Type) override
	{
		Name = "Goblin";
		Hp = 200;
		Damage = 10;
		Xp = 5;
	}
};

class Oak : public MonsterType
{
	void InsertDatabase()
	{
		Name = "Oak";
		Hp = 350;
		Damage = 15;
		Xp = 10;
	}
	virtual void BaseSetMonster(MType Type) override
	{
		Name = "Oak";
		Hp = 350;
		Damage = 15;
		Xp = 10;
	}
};

class Boss : public MonsterType
{
	void InsertDatabase()
	{
		Name = "Boss";
		Hp = 500;
		Damage = 30;
		Xp = 20;
	}
	virtual void BaseSetMonster(MType Type) override
	{
		Name = "Boss";
		Hp = 500;
		Damage = 30;
		Xp = 20;
	}
};
#endif //__MONSTERTYPE_H__