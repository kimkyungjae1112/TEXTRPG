#pragma once
#ifndef __CONTEXT_H__
#define __CONTEXT_H__
#include "Character.h"
#include "Monster.h"
#include "MapManager.h"
#include <memory>

class Context
{
public:
	static Context* GetContext();
	
	void MakeContext(Character* Player, MapManager* mapManager, class MYSQL* conn);
	void ChoiceJob();

	void InGameInterface();
	void BattleInterface();
	void EndingInterface();
	bool EndingFlag;
	bool ExitFlag;

	//Mysql
	void CleanupDatabase();
	void InsertPlayerStat();
	void InsertPlayerXp();
	void InsertPlayer(); // 저장할 때 저장하는 데이터
	void InsertMonster(MonsterType* Mt);
	void InsertJob(CharacterJob* Cj);
	void InsertBattle(const int RunFlag);
	void InsertMapManager();
	void InsertManage();

	~Context() {}
private:
	Context() {}
	Context(const Context& context) = delete;
	Context& operator=(const Context& context) = delete;

	
	int PlayerId = { 0 };

	static Context* context;

	Character* Player;
	MapManager* mapManager;
	class MYSQL* conn;
	int BattleLog = { 0 };
};

#endif // !__CONTEXT_H__
