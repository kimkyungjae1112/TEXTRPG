#pragma once
#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__
#include "Map.h"
#include "Character.h"
#include <vector>
#include <iostream>

class MapManager
{
public:
	MapManager() {}
	~MapManager();
	void AddMap(Region region);
	
	void SetMapIndex(const int& Index) { MapIndex = Index; }
	int GetMapIndex() const { return MapIndex; }
	int GetMapSize() const { return static_cast<int>(MapList.size()); }

	Map* GetMap();
	
private:
	std::vector<Map*> MapList;

	int MapIndex{ 0 };
};


#endif //__MAP_H__