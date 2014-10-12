#include <iostream>
#include <sstream>
#include "tile_map.hpp"
#include "SOIL.h"

TileMap::TileMap(const char* name)
{
    std::stringstream path;
    path << "res/level/" << name << ".tmx";
    map = TMX::parse(path.str().c_str());

    texture = SOIL_load_OGL_texture(map->tilesets[0]->image.source.c_str(),
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MULTIPLY_ALPHA);

    if(0 == texture) {
        std::stringstream error;
        error << "SOIL loading error: " << SOIL_last_result() << std::cout;
        throw error.str();
    }
}

TileMap::~TileMap()
{
}

void TileMap::Update(double delta) {

}

void TileMap::Render()
{
    // Only one tileset supported
    TSX::Tileset& tileset = *map->tilesets[0];
    glBindTexture(GL_TEXTURE_2D, texture);

    for(TMX::TileLayer* layer : map->tile_layers) {
        for(int i = 0; i < layer->height; ++i) {
            for(int j = 0; j < layer->width; ++j) {
                int tile_id = layer->tiles[i][j] - 1;

                if(tile_id == -1)
                    continue;

                glBegin(GL_QUADS);

                glTexCoord2f(
                        tileset.horizontal_ratio * (tile_id % tileset.width),
                        tileset.vertical_ratio * (tile_id / tileset.width)
                );
                glVertex2d(float(j * map->tile_width), float(i * map->tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * ((tile_id % tileset.width) + 1),
                        tileset.vertical_ratio * (tile_id / tileset.width)
                );
                glVertex2f(float((j+1) * map->tile_width), float(i * map->tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * ((tile_id % tileset.width) + 1),
                        tileset.vertical_ratio * ((tile_id / tileset.width) + 1)
                );
                glVertex2f(float((j+1) * map->tile_width), float((i+1) * map->tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * (tile_id % tileset.width),
                        tileset.vertical_ratio * ((tile_id / tileset.width) + 1)
                );
                glVertex2f(float(j * map->tile_width), float((i+1) * map->tile_height));

                glEnd();
            }
        }
    }
}
