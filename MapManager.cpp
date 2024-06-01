#include "MapManager.h"

MapManager::~MapManager()
{
	for (Map* map : MapList)
	{
		delete map;
	}
}

void MapManager::AddMap(Region region)
{
	Map* map = nullptr;

	switch (region)
	{
	case Region::GROUND:
		map = new GroudMap;
		break;
	case Region::FROZEN:
		map = new FrozenMap;
		break;
	case Region::VOLCANO:
		map = new VolcanoMap;
		break;
	default:
		map = nullptr;
		std::cout << "Àß¸øµÈ ¸Ê" << '\n';
		break;
	}

	MapList.push_back(map);
}

Map* MapManager::GetMap()
{
	if (MapIndex >= 0 && MapIndex < MapList.size())
	{
		return MapList[MapIndex];
	}
	return nullptr;
}

