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
	void CleanupDatabase(); // ���α׷��� ���� �� �����ͺ��̽� ������ ����
	void InsertPlayerStat(); // PlayerStat ���̺� ������ ����
	void InsertPlayerXp(); // PlayerXp ���̺� ������ ����
	void InsertPlayer(); // Player ���̺� ������ ����
	void InsertMonster(MonsterType* Mt); // Monster ���̺� ������ ����
	void InsertJob(CharacterJob* Cj); // Job ���̺� ������ ����
	void InsertBattle(const int RunFlag); // Battle ���̺� ������ ����
	void InsertMapManager(); // MapManager ���̺� ������ ����
	void InsertManage(); // Manage ���̺� ������ ����
	void InsertMap(Region region); // Map ���̺� ������ ����

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
