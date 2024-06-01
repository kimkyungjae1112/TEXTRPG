#include "Monster.h"
#include <iostream>

Monster::Monster() : Name(""), Hp(0), Damage(0), Xp(0), MonsterTyp(nullptr)
{
}

void Monster::BaseSetMonster(MType Type)
{
	switch (Type)
	{
	case MType::GOBLIN:
		MonsterTyp = std::make_unique<Goblin>();
		break;
	case MType::OAK:
		MonsterTyp = std::make_unique<Oak>();
		break;
	case MType::BOSS:
		MonsterTyp = std::make_unique<Boss>();
		break;
	default:
		std::cout << "잘못된 몬스터 타입" << '\n';
		break;		
	}

	MonsterTyp->BaseSetMonster(Type);
	Name = MonsterTyp->GetName();
	Hp = MonsterTyp->GetHp();
	Damage = MonsterTyp->GetDamage();
	Xp = MonsterTyp->GetXp();
}

Monster::~Monster()
{
}

