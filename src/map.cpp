#include <iostream>
#include <sstream>
#include "map.hpp"

Map::Map(const char* name)
{
    std::stringstream path;
    map = TMX::parse("res/level/", name);
    map->Print();
}

Map::~Map()
{
}

void Map::Render()
{

}
