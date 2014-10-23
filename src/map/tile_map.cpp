#include <iostream>
#include <sstream>
#include "tile_map.hpp"
#include "SOIL.h"
#include "../debug.hpp"
#include "../game.hpp"

TileMap::TileMap(const char* name)
{
    std::stringstream path;
    path << "res/level/" << name << ".tmx";
    map_ = TMX::parse(path.str().c_str());
    static_collidables_ = new Quadtree(0, Rectangle(0, 0, map_->width_pixels, map_->height_pixels));
    tileset_ = new Tileset(map_->tilesets[0]);

    // Avoid adding the same rectangle twice
    std::vector<std::vector<bool>> blocked(map_->height, std::vector<bool>(map_->width, false));
    InitBlockedTiles(map_->tile_layers_below, blocked);
    InitBlockedTiles(map_->tile_layers_above, blocked);
}

void TileMap::InitBlockedTiles(const std::vector<TMX::TileLayer*>& layers, std::vector<std::vector<bool>>& blocked) {
    TSX::Tileset* tileset = map_->tilesets[0];

    for(const auto& layer : layers) {
        // Populate blocked tiles
        for(int i = 0; i < layer->height; ++i) {
            for(int j = 0; j < layer->width; ++j) {
                if(blocked[i][j])
                    continue;

                int tile_id = layer->tiles[i][j] - 1;

                if(tileset->tiles[tile_id].Property("blocked") == "true") {
                    Rectangle* blocked_tile = new Rectangle(j*map_->tile_width, i*map_->tile_height,
                            map_->tile_width, map_->tile_height);

                    blocked_tiles_.push_back(blocked_tile);
                    static_collidables_->Insert(blocked_tile);
                    blocked[i][j] = true;
                }
            }
        }
    }
}

TileMap::~TileMap()
{
}

void TileMap::CollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const {
    static_collidables_->Retrieve(rectangle, collidables);
}

bool TileMap::IsInbounds(Rectangle* rectangle) const {
    return IsInbounds(rectangle->position(), rectangle->width(), rectangle->height());
}

bool TileMap::IsInbounds(const vec2f& position, float width, float height) const {
    return position.x >= 0.0f and position.x + width < (float)map_->width_pixels and
            position.y >= 0.0f and position.y + height < (float)map_->height_pixels;
}

void TileMap::RenderLayers(const std::vector<TMX::TileLayer*>& layers) const
{
    for(TMX::TileLayer* layer : layers)
        tileset_->RenderTiles(layer->width, layer->height, layer->tiles, Game::WIDTH, Game::HEIGHT);
}

void TileMap::RenderLayersBelow() const {
    RenderLayers(map_->tile_layers_below);
}

void TileMap::RenderLayersAbove() const {
    RenderLayers(map_->tile_layers_above);

    if(Debug::enabled) {
        for(Rectangle* r : blocked_tiles_)
            r->Render(0, 1, 0);

        static_collidables_->Render(0, 0, 1);
    }
}

void TileMap::Render() const {
    RenderLayersBelow();
    RenderLayersAbove();
}
