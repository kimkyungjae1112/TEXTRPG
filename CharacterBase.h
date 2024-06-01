#pragma once
#ifndef __CHARACTERBASE_H__
#define __CHARACTERBASE_H__
#include <iostream>
class MapManager;

enum class Job
{
	Beginner,
	Warrior,
	Wizard,
	Archer
};

class CharacterBase
{
public:
	virtual void BaseSetCharacter(Job job) = 0;
	virtual ~CharacterBase() {};

protected:
	int x{ 0 };
	int y{ 0 };
	int currentMapIndex{ 0 };

	virtual void CheckAndMoveToNextMap(MapManager* mapManager) {}
};

#endif //__CHARACTERBASE_H__