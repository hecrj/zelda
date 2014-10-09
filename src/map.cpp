#include <iostream>
#include <sstream>
#include "map.hpp"
#include "SOIL.h"

Map::Map(const char* name)
{
    std::stringstream path;
    path << "res/level/" << name << ".tmx";
    map = TMX::parse(path.str().c_str());
    map->Print();

    texture = SOIL_load_OGL_texture(map->tilesets[0]->image.source.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS);

    if(0 == texture) {
        std::stringstream error;
        error << "SOIL loading error: " << SOIL_last_result() << std::cout;
        throw error.str();
    }
}

Map::~Map()
{
}

void Map::Render()
{
    for(TMX::TileLayer* layer : map->tile_layers) {
        // Render layer here
    }
}
