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
	void CleanupDatabase(); // 프로그램이 끝날 때 데이터베이스 데이터 삭제
	void InsertPlayerStat(); // PlayerStat 테이블에 데이터 삽입
	void InsertPlayerXp(); // PlayerXp 테이블에 데이터 삽입
	void InsertPlayer(); // Player 테이블에 데이터 삽입
	void InsertMonster(MonsterType* Mt); // Monster 테이블에 데이터 삽입
	void InsertJob(CharacterJob* Cj); // Job 테이블에 데이터 삽입
	void InsertBattle(const int RunFlag); // Battle 테이블에 데이터 삽입
	void InsertMapManager(); // MapManager 테이블에 데이터 삽입
	void InsertManage(); // Manage 테이블에 데이터 삽입
	void InsertMap(Region region); // Map 테이블에 데이터 삽입

	~Context() {}
private:
	Context() {}
	Context(const Context& context) = delete;
	Context& operator=(const Context& context) = delete;
	
	static Context* context;

	Character* Player;
	MapManager* mapManager;
	class MYSQL* conn;

	int PlayerId = { 0 };
	int BattleLog = { 0 };
};

#endif // !__CONTEXT_H__
