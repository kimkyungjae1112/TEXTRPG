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
	
	void MakeContext(Character* Player, MapManager* mapManager);
	void ChoiceJob();

	void MoveInterface();
	void BattleInterface();
	void EndingInterface();
	bool EndingFlag;
	bool ExitFlag;

	~Context() {}
private:
	Context() {}
	Context(const Context& context) = delete;
	Context& operator=(const Context& context) = delete;

	static Context* context;

	Character* Player;
	MapManager* mapManager;
};

#endif // !__CONTEXT_H__
