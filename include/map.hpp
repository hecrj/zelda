#pragma once

#include "tmx_map.hpp"

class Map
{
public:
	Map(const char* s);
	virtual ~Map();

	void Render();

private:
    TMX::Map* map;
};
