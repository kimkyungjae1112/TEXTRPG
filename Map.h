#pragma once
#ifndef __MAP_H__
#define __MAP_H__

const int MaxWidth = 10;
const int MaxHeight = 10;
#include <iostream>

enum class Region
{
	GROUND,
	FROZEN,
	VOLCANO
};

class Map 
{
public:
	virtual void EnvironmentVariable() = 0;
	virtual std::string GetMapName() = 0;
	virtual ~Map() {}
};

class GroudMap : public Map
{
public:
	std::string GetMapName()
	{
		return "Ground";
	}
	virtual void EnvironmentVariable() override
	{
		std::cout << "ÇöÀç ¸Ê : Ground" << '\n';
	}
};

class FrozenMap : public Map
{
public:
	std::string GetMapName()
	{
		return "Frozen";
	}
	virtual void EnvironmentVariable() override
	{
		std::cout << "ÇöÀç ¸Ê : Frozen" << '\n';
	}
};

class VolcanoMap : public Map
{
public:
	std::string GetMapName()
	{
		return "Volcano";
	}
	virtual void EnvironmentVariable() override
	{
		std::cout << "ÇöÀç ¸Ê : Volcano" << '\n';
	}
};

#endif //__MAP_H__