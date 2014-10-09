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
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);

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
    glBindTexture(GL_TEXTURE_2D, texture);
    int tile_width_num = map->tilesets[0]->image.width / map->tilesets[0]->tile_width;
    int tile_height_num = map->tilesets[0]->image.height / map->tilesets[0]->tile_height;

    float tile_width_ratio = 1.0f / tile_width_num;
    float tile_height_ratio = 1.0f / tile_height_num;

    for(TMX::TileLayer* layer : map->tile_layers) {
        for(int i = 0; i < layer->height; ++i) {
            for(int j = 0; j < layer->width; ++j) {
                int tile_id = layer->tiles[i][j] - 1;

                if(tile_id == -1)
                    continue;

                glBegin(GL_QUADS);

                glTexCoord2f(
                        tile_width_ratio * (tile_id % tile_width_num),
                        tile_height_ratio * (tile_id / tile_width_num)
                );
                glVertex2d(float(j * map->tile_width), float(i * map->tile_height));

                glTexCoord2f(
                        tile_width_ratio * ((tile_id % tile_width_num) + 1),
                        tile_height_ratio * (tile_id / tile_width_num)
                );
                glVertex2f(float((j+1) * map->tile_width), float(i * map->tile_height));

                glTexCoord2f(
                        tile_width_ratio * ((tile_id % tile_width_num) + 1),
                        tile_height_ratio * ((tile_id / tile_width_num) + 1)
                );
                glVertex2f(float((j+1) * map->tile_width), float((i+1) * map->tile_height));

                glTexCoord2f(
                        tile_width_ratio * (tile_id % tile_width_num),
                        tile_height_ratio * ((tile_id / tile_width_num) + 1)
                );
                glVertex2f(float(j * map->tile_width), float((i+1) * map->tile_height));

                glEnd();
            }
        }
    }
}
