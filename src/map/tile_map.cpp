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

    above_index = (unsigned int) map->tile_layers.size();
    unsigned int layer_index = 0;

    for(const auto& layer : map->tile_layers) {
        if(layer->property.find("above") != layer->property.end()) {
            above_index = layer_index;
            break;
        }

        layer_index++;
    }
}

TileMap::~TileMap()
{
}

void TileMap::RenderLayers(unsigned int from, unsigned int to) const
{
    // Only one tileset supported
    TSX::Tileset& tileset = *map->tilesets[0];
    glBindTexture(GL_TEXTURE_2D, texture);

    for(; from < to; ++from) {
        TMX::TileLayer* layer = map->tile_layers[from];

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

    glBindTexture(GL_TEXTURE_2D, 0);
}

void TileMap::RenderLayersBelow() const {
    RenderLayers(0, above_index);
}

void TileMap::RenderLayersAbove() const {
    RenderLayers(above_index, (unsigned int) map->tile_layers.size());
}

void TileMap::Render() const {
    RenderLayersBelow();
    RenderLayersAbove();
}
