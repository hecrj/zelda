#include <iostream>
#include <sstream>
#include "tile_map.hpp"
#include "SOIL.h"
#include "../debug.hpp"

TileMap::TileMap(const char* name)
{
    std::stringstream path;
    path << "res/level/" << name << ".tmx";
    map_ = TMX::parse(path.str().c_str());
    collidables_ = new Quadtree(0, Rectangle(0, 0, map_->width_pixels, map_->height_pixels));
    texture = SOIL_load_OGL_texture(map_->tilesets[0]->image.source.c_str(),
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MULTIPLY_ALPHA);

    if(0 == texture) {
        std::stringstream error;
        error << "SOIL loading error: " << SOIL_last_result() << std::cout;
        throw error.str();
    }

    above_index = (unsigned int) map_->tile_layers.size();
    unsigned int layer_index = 0;
    std::vector<std::vector<bool>> blocked(map_->height, std::vector<bool>(map_->width, false));

    for(const auto& layer : map_->tile_layers) {
        if(layer->property.find("above") != layer->property.end()) {
            above_index = layer_index;
            break;
        }

        // Populate blocked tiles
        for(int i = 0; i < layer->height; ++i) {
            for(int j = 0; j < layer->width; ++j) {
                if(blocked[i][j])
                    continue;

                int tile_id = layer->tiles[i][j] - 1;

                std::map<std::string, std::string>::iterator property = map_->tilesets[0]->tiles[tile_id].property.find("blocked");

                if(property != map_->tilesets[0]->tiles[tile_id].property.end() && (*property).second == "true") {
                    blocked_tiles_.push_back(new Rectangle(j*map_->tile_width, i*map_->tile_height,
                            map_->tile_width, map_->tile_height));
                    blocked[i][j] = true;
                }
            }
        }

        layer_index++;
    }

    for(Rectangle* blocked_tile : blocked_tiles_) {
        collidables_->Insert(blocked_tile);
    }
}

TileMap::~TileMap()
{
}

void TileMap::CollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const {
    collidables_->Retrieve(rectangle, collidables);
}

bool TileMap::IsInbounds(Rectangle* rectangle) const {
    return IsInbounds(rectangle->position(), rectangle->width(), rectangle->height());
}

bool TileMap::IsInbounds(const vec2f& position, float width, float height) const {
    return position.x >= 0.0f and position.x + width < (float)map_->width_pixels and
            position.y >= 0.0f and position.y + height < (float)map_->height_pixels;
}

void TileMap::RenderLayers(unsigned int from, unsigned int to) const
{
    // Only one tileset supported
    TSX::Tileset& tileset = *map_->tilesets[0];
    glBindTexture(GL_TEXTURE_2D, texture);

    for(; from < to; ++from) {
        TMX::TileLayer* layer = map_->tile_layers[from];

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
                glVertex2d(float(j * map_->tile_width), float(i * map_->tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * ((tile_id % tileset.width) + 1),
                        tileset.vertical_ratio * (tile_id / tileset.width)
                );
                glVertex2f(float((j+1) * map_->tile_width), float(i * map_->tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * ((tile_id % tileset.width) + 1),
                        tileset.vertical_ratio * ((tile_id / tileset.width) + 1)
                );
                glVertex2f(float((j+1) * map_->tile_width), float((i+1) * map_->tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * (tile_id % tileset.width),
                        tileset.vertical_ratio * ((tile_id / tileset.width) + 1)
                );
                glVertex2f(float(j * map_->tile_width), float((i+1) * map_->tile_height));

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
    RenderLayers(above_index, (unsigned int) map_->tile_layers.size());

    if(Debug::enabled) {
        for(Rectangle* r : blocked_tiles_)
            r->Render(0, 1, 0);

        collidables_->Render();
    }
}

void TileMap::Render() const {
    RenderLayersBelow();
    RenderLayersAbove();
}
