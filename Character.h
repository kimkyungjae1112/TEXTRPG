#pragma once
#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include "CharacterBase.h"
#include "CharacterJob.h"
#include "IBattleSystem.h"
#include "MapManager.h"
#include <memory>

class Character : public CharacterBase, public BattleSystem
{
public:
	Character();

	//기본 캐릭터 설정
	virtual void BaseSetCharacter(Job job) override;

	//전투 시스템
	virtual void Attack() override;
	virtual void Defend() override;
	virtual void Run() override;
	void DetectedMonster(class Monster* InMonster);


	//이동 함수
	void MoveForward(MapManager* mapManager) ;
	void MoveBack(MapManager* mapManager) ;
	void MoveUp(MapManager* mapManager);
	void MoveDown(MapManager* mapManager);

	//Get
	std::string GetName() const { return Name; }
	int GetHp() const { return Hp; }
	int GetMp() const { return Mp; }
	int GetDamage() const { return Damage; }
	int GetXp() const { return Xp; }
	int GetLevel() const { return Level; }
	Monster* GetMonster() const { return monster; }

	friend std::ostream& operator<<(std::ostream& ost, Character* character);

	virtual ~Character();

protected:
	void CheckAndMoveToNextMap(MapManager* mapManager);
	void MeetMonster();
	void MeetBoss();
	void LevelUp(const int& InXp);

private:
	std::string Name;
	int MaxHp;
	int Hp;
	int Mp;
	int Damage;
	int Speed;
	bool RunFlag;

	int Level;
	int Xp;

	std::unique_ptr<CharacterJob> CurrentJob;
	class Monster* monster;
};

#endif //__CHARACTER_H__